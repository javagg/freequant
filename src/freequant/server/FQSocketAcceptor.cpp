#include <quickfix/HttpServer.h>
#include <quickfix/Session.h>
#include <quickfix/SessionFactory.h>
#include <quickfix/Message.h>

#include <freequant/server/FQSocketConnection.h>

#include "FQSocketAcceptor.h"

using namespace FIX;

namespace FreeQuant {

FQSocketAcceptor::FQSocketAcceptor(Application& application,
        MessageStoreFactory& factory, const SessionSettings& settings) throw(ConfigError) :
    Acceptor(application, factory, settings), m_settings(settings) {
    initialize();
}

FQSocketAcceptor::FQSocketAcceptor(Application& application,
        MessageStoreFactory& factory, const SessionSettings& settings, LogFactory& logFactory)
        throw(ConfigError) :
    Acceptor(application, factory, settings, logFactory),  m_settings(settings), m_pLogFactory(&logFactory) {
    initialize();
}

FQSocketAcceptor::~FQSocketAcceptor() {
    for (auto i = _connections.begin(); i != _connections.end(); ++i)
        delete i->second;
}

void FQSocketAcceptor::initialize() throw (ConfigError) {
    auto sessions = m_settings.getSessions();
    if (!sessions.size())
        throw ConfigError( "No sessions defined" );

    FIX::SessionFactory factory(getApplication(), getMessageStoreFactory(), m_pLogFactory);
    for (auto i = sessions.begin(); i != sessions.end(); ++i) {
        if (m_settings.get(*i).getString(CONNECTION_TYPE) == "acceptor") {
            m_sessionIDs.insert(*i);
            m_sessions[*i] = factory.create(*i, m_settings.get(*i));
        }
    }

    if (!m_sessions.size())
        throw ConfigError("No sessions defined for acceptor");
}

void FQSocketAcceptor::start() throw (ConfigError, RuntimeError) {
    Acceptor::start();
}

void FQSocketAcceptor::block() throw (ConfigError, RuntimeError) {
    Acceptor::block();
}

bool FQSocketAcceptor::poll(double timeout) throw (ConfigError, RuntimeError) {
    return Acceptor::poll(timeout);
}

void FQSocketAcceptor::stop(bool force) {
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

bool FQSocketAcceptor::isLoggedOn() {
    for (auto i = m_sessions.begin(); i != m_sessions.end(); ++i) {
      if (i->second->isLoggedOn())
        return true;
    }
    return false;
}

Session *FQSocketAcceptor::getSession(const std::string& msg, Responder& responder) {
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

const std::set<SessionID>& FQSocketAcceptor::getSessions() const {
    return m_sessionIDs;
}

Session *FQSocketAcceptor::getSession(const SessionID& sessionID) const {
    auto i = m_sessions.find( sessionID );
    if( i != m_sessions.end() )
      return i->second;
    else
      return 0;
}

const Dictionary* const FQSocketAcceptor::getSessionSettings(const SessionID& sessionID) const {
    try {
      return &m_settings.get( sessionID );
    }
    catch( ConfigError& )
    {
      return 0;
    }
}

bool FQSocketAcceptor::has(const SessionID& sessionID) {
    return m_sessions.find(sessionID) != m_sessions.end();
}

void FQSocketAcceptor::onConfigure(const SessionSettings& s) throw (ConfigError) {
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

void FQSocketAcceptor::onInitialize(const SessionSettings& s) throw(RuntimeError) {
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

void FQSocketAcceptor::onStart() {
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

bool FQSocketAcceptor::onPoll(double timeout) {
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

void FQSocketAcceptor::onStop() {}

void FQSocketAcceptor::onConnect(FIX::SocketServer& server,int accepted, int socket) {
    if (!socket_isValid( socket)) return;
    if (_connections.find(socket) != _connections.end()) return;

    int port = server.socketToPort(accepted);
    auto sessions = m_portToSessions[port];
    _connections[socket] = new FQSocketConnection(socket, sessions, &server.getMonitor());

    std::stringstream stream;
    stream << "Accepted connection from " << socket_peername(socket) << " on port " << port;

    getLog()->onEvent(stream.str());
}

void FQSocketAcceptor::onWrite(SocketServer& server, int s) {
  auto i = _connections.find( s );
  if ( i == _connections.end() ) return ;
  FQSocketConnection* socketConnection = i->second;
  if( socketConnection->processQueue() )
    socketConnection->unsignal();

}

bool FQSocketAcceptor::onData(SocketServer& server, int s) {
    auto i = _connections.find(s);
    if (i == _connections.end()) return false;

    FQSocketConnection *socketConnection = i->second;
    return socketConnection->read(*this, server);
}

void FQSocketAcceptor::onDisconnect(SocketServer&, int s) {
    auto i = _connections.find(s);
    if (i == _connections.end()) return;

    FQSocketConnection *socketConnection = i->second;
    Session *session = socketConnection->getSession();
    if (session)
        session->disconnect();

    delete socketConnection;
    _connections.erase(s);
}

void FQSocketAcceptor::onError(SocketServer&) {}

void FQSocketAcceptor::onTimeout(SocketServer&) {
  for (auto i = _connections.begin(); i != _connections.end(); ++i )
    i->second->onTimeout();
}

} // namespace FreeQuant
