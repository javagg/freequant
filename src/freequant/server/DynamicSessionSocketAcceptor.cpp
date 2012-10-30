#include <quickfix/Session.h>

#include <freequant/server/FQSocketConnection.h>

#include "DynamicSessionSocketAcceptor.h"

using namespace FIX;

namespace FreeQuant {

DynamicSessionSocketAcceptor::DynamicSessionSocketAcceptor(Application& application,
        MessageStoreFactory& factory, const SessionSettings& settings) throw(ConfigError) :
    Acceptor(application, factory, settings) {
}

DynamicSessionSocketAcceptor::DynamicSessionSocketAcceptor(Application& application,
        MessageStoreFactory& factory, const SessionSettings& settings, LogFactory& logFactory)
        throw(ConfigError) :
    Acceptor(application, factory, settings, logFactory) {
}

DynamicSessionSocketAcceptor::~DynamicSessionSocketAcceptor() {
    for (auto i = _connections.begin(); i != _connections.end(); ++i)
        delete i->second;
}

void DynamicSessionSocketAcceptor::onConfigure(const SessionSettings& s) throw (ConfigError) {
    auto sessions = s.getSessions();
    for(auto i = sessions.begin(); i != sessions.end(); ++i) {
        auto settings = s.get(*i);
        settings.getLong(SOCKET_ACCEPT_PORT);
        if (settings.has(SOCKET_REUSE_ADDRESS))
            settings.getBool( SOCKET_REUSE_ADDRESS);
        if (settings.has(SOCKET_NODELAY))
            settings.getBool(SOCKET_NODELAY);
    }
}

void DynamicSessionSocketAcceptor::onInitialize(const SessionSettings& s) throw(RuntimeError) {
    short port = 0;
    try {
        _server.reset(new SocketServer(1));

    std::set<SessionID> sessions = s.getSessions();
    std::set<SessionID>::iterator i = sessions.begin();
    for( ; i != sessions.end(); ++i )
    {
      Dictionary settings = s.get( *i );  time_t start = 0;
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

      short port = (short)settings.getLong( SOCKET_ACCEPT_PORT );

      const bool reuseAddress = settings.has( SOCKET_REUSE_ADDRESS ) ?
        s.get().getBool( SOCKET_REUSE_ADDRESS ) : true;

      const bool noDelay = settings.has( SOCKET_NODELAY ) ?
        s.get().getBool( SOCKET_NODELAY ) : false;

      const int sendBufSize = settings.has( SOCKET_SEND_BUFFER_SIZE ) ?
        s.get().getLong( SOCKET_SEND_BUFFER_SIZE ) : 0;

      const int rcvBufSize = settings.has( SOCKET_RECEIVE_BUFFER_SIZE ) ?
        s.get().getLong( SOCKET_RECEIVE_BUFFER_SIZE ) : 0;

      m_portToSessions[port].insert( *i );
      _server->add( port, reuseAddress, noDelay, sendBufSize, rcvBufSize );  time_t start = 0;
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

    }
    } catch(SocketException& e) {
        throw RuntimeError("Unable to create, bind, or listen to port "
            + IntConvertor::convert((unsigned short)port) + " (" + e.what() + ")");
    }
}

void DynamicSessionSocketAcceptor::onStart() {
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

bool DynamicSessionSocketAcceptor::onPoll(double timeout) {
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

void DynamicSessionSocketAcceptor::onStop() {}

void DynamicSessionSocketAcceptor::onConnect( FIX::SocketServer& server, int a, int s )
{
  if ( !socket_isValid( s ) ) return;
  auto i = _connections.find( s );
  if ( i != _connections.end() ) return;
  int port = server.socketToPort( a );
  Sessions sessions = m_portToSessions[port];
  _connections[ s ] = new FQSocketConnection( s, sessions, &server.getMonitor() );

  std::stringstream stream;
  stream << "Accepted connection from " << socket_peername( s ) << " on port " << port;

  if( getLog() )
    getLog()->onEvent( stream.str() );
}

void DynamicSessionSocketAcceptor::onWrite(SocketServer& server, int s) {
  auto i = _connections.find( s );
  if ( i == _connections.end() ) return ;
  FQSocketConnection* socketConnection = i->second;
  if( socketConnection->processQueue() )
    socketConnection->unsignal();

}

bool DynamicSessionSocketAcceptor::onData(SocketServer& server, int s) {
    auto i = _connections.find(s);
    if (i == _connections.end()) return false;

    FQSocketConnection *socketConnection = i->second;
    return socketConnection->read(*this, server);
}

void DynamicSessionSocketAcceptor::onDisconnect(SocketServer&, int s) {
    auto i = _connections.find(s);
    if (i == _connections.end()) return;

    FQSocketConnection *socketConnection = i->second;
    Session *session = socketConnection->getSession();
    if (session)
        session->disconnect();

    delete socketConnection;
    _connections.erase(s);
}

void DynamicSessionSocketAcceptor::onError(SocketServer&) {}

void DynamicSessionSocketAcceptor::onTimeout(SocketServer&) {
  for (auto i = _connections.begin(); i != _connections.end(); ++i )
    i->second->onTimeout();
}

} // namespace FreeQuant
