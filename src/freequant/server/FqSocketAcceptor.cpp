#include <boost/algorithm/cxx11/any_of.hpp>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/stl/container.hpp>

#include <quickfix/HttpServer.h>
#include <quickfix/Session.h>
#include <quickfix/SessionFactory.h>
#include <quickfix/Message.h>

#include <freequant/server/FqSocketConnection.h>
#include "FqSocketAcceptor.h"

using namespace boost::phoenix;
using namespace boost::algorithm;
using namespace FIX;

namespace FreeQuant {

FqSocketAcceptor::FqSocketAcceptor(Application& application,
        MessageStoreFactory& factory, const SessionSettings& settings) throw(ConfigError) :
    Acceptor(application, factory, settings), _settings(settings) {
    initialize();
}

FqSocketAcceptor::FqSocketAcceptor(Application& application,
        MessageStoreFactory& factory, const SessionSettings& settings, LogFactory& logFactory)
        throw(ConfigError) :
    Acceptor(application, factory, settings, logFactory),  _settings(settings), m_pLogFactory(&logFactory) {
    initialize();
}

FqSocketAcceptor::~FqSocketAcceptor() {
    for (auto i = _connections.begin(); i != _connections.end(); ++i)
        delete i->second;
}

void FqSocketAcceptor::initialize() throw (ConfigError) {
    auto sessions = _settings.getSessions();
    if (!sessions.size())
        throw ConfigError( "No sessions defined" );

    FIX::SessionFactory factory(getApplication(), getMessageStoreFactory(), m_pLogFactory);
    for (auto i = sessions.begin(); i != sessions.end(); ++i) {
        if (_settings.get(*i).getString(CONNECTION_TYPE) == "acceptor") {
            m_sessionIDs.insert(*i);
            m_sessions[*i] = factory.create(*i, _settings.get(*i));
        }
    }

    if (!m_sessions.size())
        throw ConfigError("No sessions defined for acceptor");
}

void FqSocketAcceptor::start() throw (ConfigError, RuntimeError) {
    Acceptor::start();
}

void FqSocketAcceptor::block() throw (ConfigError, RuntimeError) {
    Acceptor::block();
}

bool FqSocketAcceptor::poll(double timeout) throw (ConfigError, RuntimeError) {
    return Acceptor::poll(timeout);
}

void FqSocketAcceptor::stop(bool force) {
    Acceptor::stop(force);

    std::vector<Session*> enabledSessions;

    for (auto i = m_sessions.begin(); i != m_sessions.end(); ++i )
    {
      Session* pSession = Session::lookupSession(i->first);
      if( pSession->isEnabled() )
      {
        enabledSessions.push_back( pSession );
        pSession->logout();
        Session::unregisterSession( pSession->getSessionID() );
      }
    }

    for(auto session = enabledSessions.begin(); session != enabledSessions.end(); ++session )
      (*session)->logon();
}

bool FqSocketAcceptor::isLoggedOn() {
//    using boost::phoenix::arg_names::arg1;
//    any_of(m_sessions.begin(), m_sessions.end(), arg1.second->isLoggedOn());
    for (auto i = m_sessions.begin(); i != m_sessions.end(); ++i) {
      if (i->second->isLoggedOn())
        return true;
    }
    return false;
}

Session *FqSocketAcceptor::getSession(const std::string& msg, Responder& responder) {
    Message message;
    if (!message.setStringHeader(msg))
        return 0;

    BeginString beginString;
    SenderCompID senderCompID;
    TargetCompID targetCompID;
    MsgType msgType;
    try {
        auto header = message.getHeader();
        header.getField(beginString);
        header.getField(senderCompID);
        header.getField(targetCompID);
        header.getField(msgType);
        if (msgType != MsgType_Logon)
            return 0;

        SessionID sessionID(beginString, SenderCompID(targetCompID), TargetCompID(senderCompID));
        auto i = m_sessions.find(sessionID);
        if (i != m_sessions.end()) {
            i->second->setResponder(&responder);
            return i->second;
        }
    } catch (FieldNotFound&) {}
    return 0;
}

const std::set<SessionID>& FqSocketAcceptor::getSessions() const {
    return m_sessionIDs;
}

Session *FqSocketAcceptor::getSession(const SessionID& sessionID) const {
    auto i = m_sessions.find( sessionID );
    if( i != m_sessions.end() )
      return i->second;
    else
      return 0;
}

const Dictionary* const FqSocketAcceptor::getSessionSettings(const SessionID& sessionID) const {
    try {
      return &_settings.get( sessionID );
    }
    catch( ConfigError& )
    {
      return 0;
    }
}

bool FqSocketAcceptor::has(const SessionID& sessionID) {
    return m_sessions.find(sessionID) != m_sessions.end();
}

void FqSocketAcceptor::onConfigure(const SessionSettings& s) throw (ConfigError) {
//    auto sessions = s.getSessions();
//    for(auto i = sessions.begin(); i != sessions.end(); ++i) {
//        auto settings = s.get(*i);
//        settings.getLong(SOCKET_ACCEPT_PORT);
//        if (settings.has(SOCKET_REUSE_ADDRESS))
//            settings.getBool( SOCKET_REUSE_ADDRESS);
//        if (settings.has(SOCKET_NODELAY))
//            settings.getBool(SOCKET_NODELAY);
//    }
}

void FqSocketAcceptor::onInitialize(const SessionSettings& s) throw(RuntimeError) {
    long port = 0;
    try {
        _server.reset(new SocketServer(1));

        std::set<SessionID> sessions = s.getSessions();
        for (auto i = sessions.begin(); i != sessions.end(); ++i) {
          Dictionary dictionary = s.get( *i );
          port = dictionary.getLong( SOCKET_ACCEPT_PORT );
          bool reuseAddress = dictionary.has(SOCKET_REUSE_ADDRESS) ?
            s.get().getBool( SOCKET_REUSE_ADDRESS ) : true;
          bool noDelay = dictionary.has( SOCKET_NODELAY ) ?
            s.get().getBool( SOCKET_NODELAY ) : false;
          int sendBufSize = dictionary.has( SOCKET_SEND_BUFFER_SIZE ) ?
            s.get().getLong( SOCKET_SEND_BUFFER_SIZE ) : 0;
          int rcvBufSize = dictionary.has( SOCKET_RECEIVE_BUFFER_SIZE ) ?
            s.get().getLong( SOCKET_RECEIVE_BUFFER_SIZE ) : 0;
          m_portToSessions[port].insert(*i);
          _server->add(port, reuseAddress, noDelay, sendBufSize, rcvBufSize);
        }
    } catch(SocketException& e) {
        throw RuntimeError("Unable to create, bind, or listen to port "
            + IntConvertor::convert((unsigned short)port) + " (" + e.what() + ")");
    }
}

void FqSocketAcceptor::onStart() {
    while (!isStopped() && bool(_server) && _server->block(*this)) {}

    if (!_server) return;

    time_t start = 0;
    time_t now = 0;

    ::time(&start);
    while (isLoggedOn()) {
        _server->block(*this);
        if (::time(&now)-5 >= start)
            break;
    }
    _server->close();
    _server.reset();
}

bool FqSocketAcceptor::onPoll(double timeout) {
    if (!_server) return false;

    time_t start = 0;
    time_t now = 0;

    if (isStopped()) {
        if (start == 0)
            ::time(&start);
        if (!isLoggedOn()) {
            start = 0;
            return false;
        }
        if (::time(&now)-5 >= start) {
            start = 0;
            return false;
        }
    }

    _server->block(*this, true, timeout);
    return true;
}

void FqSocketAcceptor::onStop() {}

void FqSocketAcceptor::onConnect(FIX::SocketServer& server,int accepted, int socket) {
    if (!socket_isValid( socket)) return;
    if (_connections.find(socket) != _connections.end()) return;

    int port = server.socketToPort(accepted);
    auto sessions = m_portToSessions[port];
    _connections[socket] = new FqSocketConnection(socket, sessions, &server.getMonitor());

    std::stringstream stream;
    stream << "Accepted connection from " << socket_peername(socket) << " on port " << port;

    getLog()->onEvent(stream.str());
}

void FqSocketAcceptor::onWrite(SocketServer& server, int s) {
  auto i = _connections.find( s );
  if ( i == _connections.end() ) return ;
  FqSocketConnection* socketConnection = i->second;
  if( socketConnection->processQueue() )
    socketConnection->unsignal();

}

bool FqSocketAcceptor::onData(SocketServer& server, int s) {
    auto i = _connections.find(s);
    if (i == _connections.end()) return false;

    FqSocketConnection *socketConnection = i->second;
    return socketConnection->read(*this, server);
}

void FqSocketAcceptor::onDisconnect(SocketServer&, int s) {
    auto i = _connections.find(s);
    if (i == _connections.end()) return;

    FqSocketConnection *socketConnection = i->second;
    Session *session = socketConnection->getSession();
    if (session)
        session->disconnect();

    delete socketConnection;
    _connections.erase(s);
}

void FqSocketAcceptor::onError(SocketServer&) {}

void FqSocketAcceptor::onTimeout(SocketServer&) {
  for (auto i = _connections.begin(); i != _connections.end(); ++i )
    i->second->onTimeout();
}

} // namespace FreeQuant
