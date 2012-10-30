#include <quickfix/Session.h>

#include "DynamicSessionSocketAcceptor.h"

using namespace FIX;

namespace FreeQuant {

DynamicSessionSocketAcceptor::DynamicSessionSocketAcceptor(Application& application,
        MessageStoreFactory& factory, const SessionSettings& settings) throw(ConfigError) :
    SocketAcceptor(application, factory, settings)
//  , m_pServer(0)
{
}

DynamicSessionSocketAcceptor::DynamicSessionSocketAcceptor(Application& application,
        MessageStoreFactory& factory, const SessionSettings& settings, LogFactory& logFactory)
        throw(ConfigError) :
    SocketAcceptor(application, factory, settings, logFactory)
//  , m_pServer(0)
{
}

DynamicSessionSocketAcceptor::~DynamicSessionSocketAcceptor() {
//    for (auto i = m_connections.begin(); i != m_connections.end(); ++i)
//        delete i->second;
}

void DynamicSessionSocketAcceptor::onConfigure(const SessionSettings& s) throw (ConfigError) {
  std::set<SessionID> sessions = s.getSessions();
  std::set<SessionID>::iterator i;
  for( i = sessions.begin(); i != sessions.end(); ++i ) {
    const Dictionary& settings = s.get(*i);
    settings.getLong( SOCKET_ACCEPT_PORT );
    if( settings.has(SOCKET_REUSE_ADDRESS) )
      settings.getBool( SOCKET_REUSE_ADDRESS );
    if( settings.has(SOCKET_NODELAY) )
      settings.getBool( SOCKET_NODELAY );
  }
}

void DynamicSessionSocketAcceptor::onInitialize(const SessionSettings& s) throw(RuntimeError) {
    short port = 0;

//  try
//  {
//    m_pServer = new SocketServer( 1 );

//    std::set<SessionID> sessions = s.getSessions();
//    std::set<SessionID>::iterator i = sessions.begin();
//    for( ; i != sessions.end(); ++i )
//    {
//      Dictionary settings = s.get( *i );
//      short port = (short)settings.getLong( SOCKET_ACCEPT_PORT );

//      const bool reuseAddress = settings.has( SOCKET_REUSE_ADDRESS ) ?
//        s.get().getBool( SOCKET_REUSE_ADDRESS ) : true;

//      const bool noDelay = settings.has( SOCKET_NODELAY ) ?
//        s.get().getBool( SOCKET_NODELAY ) : false;

//      const int sendBufSize = settings.has( SOCKET_SEND_BUFFER_SIZE ) ?
//        s.get().getLong( SOCKET_SEND_BUFFER_SIZE ) : 0;

//      const int rcvBufSize = settings.has( SOCKET_RECEIVE_BUFFER_SIZE ) ?
//        s.get().getLong( SOCKET_RECEIVE_BUFFER_SIZE ) : 0;

//      m_portToSessions[port].insert( *i );
//      m_pServer->add( port, reuseAddress, noDelay, sendBufSize, rcvBufSize );
//    }
//  }
//  catch( SocketException& e )
//  {
//    throw RuntimeError( "Unable to create, bind, or listen to port "
//                       + IntConvertor::convert( (unsigned short)port ) + " (" + e.what() + ")" );
//  }

}

void DynamicSessionSocketAcceptor::onStart() {
//    while ( !isStopped() && m_pServer && m_pServer->block( *this ) ) {}

//  if( !m_pServer )
//    return;

//  time_t start = 0;
//  time_t now = 0;

//  ::time( &start );
//  while ( isLoggedOn() )
//  {
//    m_pServer->block( *this );
//    if( ::time(&now) -5 >= start )
//      break;
//  }

//  m_pServer->close();
//  delete m_pServer;
//  m_pServer = 0;

}

bool DynamicSessionSocketAcceptor::onPoll( double timeout )
{
//  if( !m_pServer )
//    return false;

//  time_t start = 0;
//  time_t now = 0;

//  if( isStopped() )
//  {
//    if( start == 0 )
//      ::time( &start );
//    if( !isLoggedOn() )
//    {
//      start = 0;
//      return false;
//    }
//    if( ::time(&now) - 5 >= start )
//    {
//      start = 0;
//      return false;
//    }
//  }

//  m_pServer->block( *this, true, timeout );
  return true;

}

void DynamicSessionSocketAcceptor::onStop()
{
}

void DynamicSessionSocketAcceptor::onConnect( FIX::SocketServer& server, int a, int s )
{
//  if ( !socket_isValid( s ) ) return;
//  SocketConnections::iterator i = m_connections.find( s );
//  if ( i != m_connections.end() ) return;
//  int port = server.socketToPort( a );
//  Sessions sessions = m_portToSessions[port];
//  m_connections[ s ] = new SocketConnection( s, sessions, &server.getMonitor() );

//  std::stringstream stream;
//  stream << "Accepted connection from " << socket_peername( s ) << " on port " << port;

//  if( getLog() )
//    getLog()->onEvent( stream.str() );
}

void DynamicSessionSocketAcceptor::onWrite(FIX::SocketServer& server, int s )
{
//  SocketConnections::iterator i = m_connections.find( s );
//  if ( i == m_connections.end() ) return ;
//  SocketConnection* pSocketConnection = i->second;
//  if( pSocketConnection->processQueue() )
//    pSocketConnection->unsignal();

}

bool DynamicSessionSocketAcceptor::onData( FIX::SocketServer& server, int s ){
//  auto i = m_connections.find(s);
//    if (i == m_connections.end()) return false;
//  SocketConnection* pSocketConnection = i->second;
//  return pSocketConnection->read( *this, server );
    return true;
}

void DynamicSessionSocketAcceptor::onDisconnect( SocketServer&, int s )
{
//  SocketConnections::iterator i = m_connections.find( s );
//  if ( i == m_connections.end() ) return ;
//  SocketConnection* pSocketConnection = i->second;

//  Session* pSession = pSocketConnection->getSession();
//  if ( pSession ) pSession->disconnect();

//  delete pSocketConnection;
//  m_connections.erase( s );

}

void DynamicSessionSocketAcceptor::onError(FIX::SocketServer&) {}

void DynamicSessionSocketAcceptor::onTimeout(FIX::SocketServer&) {
    SocketConnections::iterator i;
//  for ( i = m_connections.begin(); i != m_connections.end(); ++i )
//    i->second->onTimeout();

}

} // namespace FreeQuant
