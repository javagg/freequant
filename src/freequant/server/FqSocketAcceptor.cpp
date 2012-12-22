#include <boost/enable_shared_from_this.hpp>
#include <boost/algorithm/cxx11/any_of.hpp>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/stl/container.hpp>
#include <boost/thread/thread.hpp>

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
}

FqSocketAcceptor::FqSocketAcceptor(Application& application,
        MessageStoreFactory& factory, const SessionSettings& settings, LogFactory& logFactory)
        throw(ConfigError) :
    Acceptor(application, factory, settings, logFactory),  _settings(settings), m_pLogFactory(&logFactory) {
}

FqSocketAcceptor::~FqSocketAcceptor() {
    for (auto i = _connections.begin(); i != _connections.end(); ++i)
        delete i->second;
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

void FqSocketAcceptor::createSession() {
    // create a new session from nothing
    SessionFactory *f = new SessionFactory(getApplication(), getMessageStoreFactory(), m_pLogFactory);
    BeginString beginString = "FIX4.4";
    SenderCompID senderCompID = "senderCompID";
    TargetCompID targetCompID = "senderCompID";
    SessionID sId(beginString, senderCompID, targetCompID);
    FIX::Dictionary dict;
    _settings.set(sId, dict);
    Session *s = f->create(sId, dict);
    delete s;
    delete f;
}

SocketAcceptor::SocketAcceptor(FIX::Application& application,
    FIX::MessageStoreFactory& messageStoreFactory,
    const FIX::SessionSettings& settings) throw(FIX::ConfigError) :
    m_application(application), m_messageStoreFactory(messageStoreFactory),
    m_settings(settings), m_pLogFactory(0), m_pLog(0),
    m_stop(true),
    _acceptor(_io_service) {
    initialize();
}

SocketAcceptor::SocketAcceptor(FIX::Application& application,
    FIX::MessageStoreFactory& messageStoreFactory,
    const FIX::SessionSettings& settings, FIX::LogFactory& logFactory) throw(FIX::ConfigError) :
    m_application(application), m_messageStoreFactory(messageStoreFactory),
    m_settings(settings), m_pLogFactory(&logFactory), m_pLog(0),
    m_stop(true),
    _acceptor(_io_service) {
    initialize();
}

SocketAcceptor::~SocketAcceptor() {}

void SocketAcceptor::initialize() {
    std::set <SessionID> sessions = m_settings.getSessions();
    if (!sessions.size())
        throw ConfigError("No sessions defined");
    SessionFactory factory(m_application, m_messageStoreFactory, m_pLogFactory);

    std::for_each(sessions.begin(), sessions.end(), [&](const SessionID& id) {
        if (m_settings.get(id).getString(CONNECTION_TYPE) == "acceptor") {
            m_sessionIDs.insert(id);
            m_sessions[id] = factory.create(id, m_settings.get(id));
        }
    });

    if (!m_sessions.size())
        throw ConfigError("No sessions defined for acceptor");
}

void SocketAcceptor::start() throw (FIX::ConfigError, FIX::RuntimeError) {
    m_stop = false;
    onConfigure(m_settings);
    onInitialize(m_settings);

    // TODO: what's going on?
    HttpServer::startGlobal( m_settings );

    boost::thread thread([&]() {
        onStart();
        _io_service.run();
    });
}

void SocketAcceptor::stop(bool force) {
    if (isStopped()) return;

    // TODO: what's going on?
    HttpServer::stopGlobal();

    std::vector<Session*> enabledSessions;

    for (auto i = m_sessions.begin(); i != m_sessions.end(); ++i) {
        Session* pSession = Session::lookupSession(i->first);
        if (pSession->isEnabled()) {
            enabledSessions.push_back(pSession);
            pSession->logout();
            Session::unregisterSession(pSession->getSessionID());
        }
    }

//    if (!force) {
//        for (int second = 1; second <= 10 && isLoggedOn(); ++second)
//            process_sleep(1);
//    }

    m_stop = true;
//    onStop();

//    if (m_threadid)
//        thread_join(m_threadid);
//    m_threadid = 0;

//    std::for_each(enabledSessions.begin(), enabledSessions.end(), [](const Session* s) {
//        s->logon();
//    });

//    std::vector<Session*>::iterator session = enabledSessions.begin();
//      for( ; session != enabledSessions.end(); ++session )
//       (*session)->logon();
}

bool SocketAcceptor::isStopped() {
    return m_stop;
}

void SocketAcceptor::onConfigure(const FIX::SessionSettings&) throw (FIX::ConfigError) {

}

void SocketAcceptor::onInitialize(const FIX::SessionSettings&) throw (FIX::RuntimeError) {

}

void SocketAcceptor::onStart() {
    using namespace boost::asio;
    ip::tcp::endpoint endpoint(ip::tcp::v4(), 7711);
    _acceptor.open(endpoint.protocol());
    _acceptor.set_option(ip::tcp::acceptor::reuse_address(true));
    _acceptor.bind(endpoint);
    _acceptor.listen();
    accept();
}

void SocketAcceptor::onConnect(FIX::SocketServer&, int acceptSocket, int socket) {

}

void SocketAcceptor::onWrite(FIX::SocketServer&, int socket) {

}

bool SocketAcceptor::onData(FIX::SocketServer&, int socket) {
    return true;
}

void SocketAcceptor::onDisconnect(FIX::SocketServer&, int socket) {

}

void SocketAcceptor::onError(FIX::SocketServer&) {

}

void SocketAcceptor::onTimeout(FIX::SocketServer&) {

}

class SocketConnection : public boost::enable_shared_from_this<SocketConnection> {
public:
    SocketConnection(boost::asio::io_service& io_service) : _socket(io_service) {}
    boost::asio::ip::tcp::socket& socket() { return _socket; }
    void start() {
        _socket.async_read_some(boost::asio::buffer(_data, _data.size()),
            boost::bind(&SocketConnection::handleRead, this, boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }

    void handleRead(const boost::system::error_code& error, size_t transferred) {
        if (!error) {
            std::cout << _data.data() << std::endl;
//            _parser.addToStream(_data.data(), transferred);

//            std::string message;
    //        if (!_session) {
//                if (!readMessage(message)) {
    //                _session = FIX::Session::lookupSession(message, true);
    //                if (!_session) {
    //                   FIX::Message fixMessage;
    //                   if (fixMessage.setStringHeader(message)) {
    //                       const FIX::Header& header = fixMessage.getHeader();
    //                       const FIX::BeginString& beginString = FIELD_GET_REF(header, BeginString );
    //                       const FIX::SenderCompID& senderCompID = FIELD_GET_REF(header, SenderCompID );
    //                       const FIX::TargetCompID& targetCompID = FIELD_GET_REF(header, TargetCompID );

    //                       FIX::SessionID sessionID(beginString, FIX::SenderCompID(targetCompID), FIX::TargetCompID( senderCompID));
    //                       if (_callback) _callback->onNewSession(sessionID);
    ////                           new Session(application, MessageStoreFactory&,
    ////                                    const SessionID&,
    ////                                    const DataDictionaryProvider&,
    ////                                    const TimeRange&,
    ////                                    int heartBtInt, LogFactory* pLogFactory );
    //                       _session = FIX::Session::lookupSession(message, true);
    //                   }
    //                }

    //                if (_session) {
    //                    FIX::Session::registerSession(_session->getSessionID());
//                    }
//                }
    //        }

//            readMessages();
            _socket.async_read_some(boost::asio::buffer(_data, _data.size()),
                boost::bind(&SocketConnection::handleRead, this, boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
        } else {
            _socket.close();
            std::cout << error.message() << std::endl;
        }
}

private:
    boost::asio::ip::tcp::socket _socket;
    boost::array<char, 4096> _data;
    FIX::Parser _parser;
};

void SocketAcceptor::accept() {
    boost::shared_ptr<SocketConnection> connection(new SocketConnection(_io_service));
    _acceptor.async_accept(connection->socket(), [&](const boost::system::error_code& error) {
        if (!error) {
            connection->start();
        } else {
            std::cout << "error in " << __FUNCTION__ << ": " << error.message() << std::endl;
        }
        this->accept();
    });
}

void SocketAcceptor::handleRead(const boost::system::error_code& error, size_t transferred) {
//    if (!error) {
//        std::cout << _data.data() << std::endl;
//        _parser.addToStream(_data.data(), transferred);

//        std::string message;
////        if (!_session) {
//            if (!readMessage(message)) {
////                _session = FIX::Session::lookupSession(message, true);
////                if (!_session) {
////                   FIX::Message fixMessage;
////                   if (fixMessage.setStringHeader(message)) {
////                       const FIX::Header& header = fixMessage.getHeader();
////                       const FIX::BeginString& beginString = FIELD_GET_REF(header, BeginString );
////                       const FIX::SenderCompID& senderCompID = FIELD_GET_REF(header, SenderCompID );
////                       const FIX::TargetCompID& targetCompID = FIELD_GET_REF(header, TargetCompID );

////                       FIX::SessionID sessionID(beginString, FIX::SenderCompID(targetCompID), FIX::TargetCompID( senderCompID));
////                       if (_callback) _callback->onNewSession(sessionID);
//////                           new Session(application, MessageStoreFactory&,
//////                                    const SessionID&,
//////                                    const DataDictionaryProvider&,
//////                                    const TimeRange&,
//////                                    int heartBtInt, LogFactory* pLogFactory );
////                       _session = FIX::Session::lookupSession(message, true);
////                   }
////                }

////                if (_session) {
////                    FIX::Session::registerSession(_session->getSessionID());
//                }
//            }
////        }

//        readMessages();
//        _socket.async_read_some(boost::asio::buffer(_data, _data.size()),
//            boost::bind(&SocketAcceptor::handleRead, this, boost::asio::placeholders::error,

//                        boost::asio::placeholders::bytes_transferred));

////    } else {
////        std::cout << error.message() << std::endl;
////    }
}

void SocketAcceptor::handleWrite(const boost::system::error_code& error, size_t bytes_transferred) {
//    if (error) {
////            close();
//    }
////        if (!error) {
////        socket_.async_read_some(boost::asio::buffer(data_, max_length),
////            boost::bind(&session::handle_read, this,
////              boost::asio::placeholders::error,
////              boost::asio::placeholders::bytes_transferred));
////      }
////      else
////      {
////        delete this;
////      }
}

bool SocketAcceptor::readMessage(std::string& message) {
//    try {
//        return _parser.readFixMessage(message);
//    } catch (FIX::MessageParseError&) {}
    return true;
}

void SocketAcceptor::readMessages() {
//    std::string message;
//    while (readMessage(message)) {
//        try {
////            _session->next(message, FIX::UtcTimeStamp());
//        } catch (FIX::InvalidMessage&) {
////            if (!_session->isLoggedOn()) {
//            }
//        }
//    }
}

} // namespace FreeQuant
