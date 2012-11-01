#include "FqSocketConnection.h"

#include <quickfix/Utility.h>

using namespace FIX;

namespace FreeQuant {


FqSocketConnection::FqSocketConnection( int s, Sessions sessions,
                                    SocketMonitor* pMonitor )
: m_socket( s ), m_sendLength( 0 ),
  m_sessions(sessions), m_pSession( 0 ), m_pMonitor( pMonitor )
{
  FD_ZERO( &m_fds );
  FD_SET( m_socket, &m_fds );
}

FqSocketConnection::FqSocketConnection( SocketInitiator& i,
                                    const SessionID& sessionID, int s,
                                    SocketMonitor* pMonitor )
: m_socket( s ), m_sendLength( 0 ),
  m_pSession( i.getSession( sessionID, *this ) ),
  m_pMonitor( pMonitor )
{
  FD_ZERO( &m_fds );
  FD_SET( m_socket, &m_fds );
  m_sessions.insert( sessionID );
}

FqSocketConnection::~FqSocketConnection()
{
  if ( m_pSession )
    Session::unregisterSession( m_pSession->getSessionID() );
}

bool FqSocketConnection::send( const std::string& msg )
{
  Locker l( m_mutex );

  m_sendQueue.push_back( msg );
  processQueue();
  signal();
  return true;

}

bool FqSocketConnection::processQueue()
{
  Locker l( m_mutex );

  if( !m_sendQueue.size() ) return true;

  struct timeval timeout = { 0, 0 };
  fd_set writeset = m_fds;
  if( select( 1 + m_socket, 0, &writeset, 0, &timeout ) <= 0 )
    return false;

  const std::string& msg = m_sendQueue.front();

  int result = socket_send
    ( m_socket, msg.c_str() + m_sendLength, msg.length() - m_sendLength );

  if( result > 0 )
    m_sendLength += result;

  if( m_sendLength == msg.length() )
  {
    m_sendLength = 0;
    m_sendQueue.pop_front();
  }

  return !m_sendQueue.size();

}

void FqSocketConnection::disconnect()
{
  if ( m_pMonitor )
    m_pMonitor->drop( m_socket );


}

bool FqSocketConnection::read( SocketConnector& s )
{
  if ( !m_pSession ) return false;

  try
  {
    readFromSocket();
    readMessages( s.getMonitor() );
  }
  catch( SocketRecvFailed& e )
  {
    m_pSession->getLog()->onEvent( e.what() );
    return false;
  }
  return true;

}

bool FqSocketConnection::read(FreeQuant::FqSocketAcceptor& a, SocketServer& s )
{
    std::string msg;
  try
  {
    readFromSocket();

    if ( !m_pSession )
    {
      if ( !readMessage( msg ) ) return false;
      m_pSession = Session::lookupSession( msg, true );
      if( !isValidSession() )
      {
        m_pSession = 0;
        if( a.getLog() )
        {
          a.getLog()->onEvent( "Session not found for incoming message: " + msg );
          a.getLog()->onIncoming( msg );
        }
      }
      if( m_pSession )
        m_pSession = a.getSession( msg, *this );
      if( m_pSession )
        m_pSession->next( msg, UtcTimeStamp() );
      if( !m_pSession )
      {
        s.getMonitor().drop( m_socket );
        return false;
      }

      Session::registerSession( m_pSession->getSessionID() );
    }

    readMessages( s.getMonitor() );
    return true;
  }
  catch ( SocketRecvFailed& e )
  {
    if( m_pSession )
      m_pSession->getLog()->onEvent( e.what() );
    s.getMonitor().drop( m_socket );
  }
  catch ( InvalidMessage& )
  {
    s.getMonitor().drop( m_socket );
  }
  return false;

}

bool FqSocketConnection::isValidSession()
{
  if( m_pSession == 0 )
    return false;
  SessionID sessionID = m_pSession->getSessionID();
  if( Session::isSessionRegistered(sessionID) )
    return false;
  return !( m_sessions.find(sessionID) == m_sessions.end() );


}

void FqSocketConnection::readFromSocket()
throw( SocketRecvFailed )
{
  int size = recv( m_socket, m_buffer, sizeof(m_buffer), 0 );
  if( size <= 0 ) throw SocketRecvFailed( size );
  m_parser.addToStream( m_buffer, size );


}

bool FqSocketConnection::readMessage( std::string& msg )
{
  try
  {
    return m_parser.readFixMessage( msg );
  }
  catch ( MessageParseError& ) {}
  return true;

}

void FqSocketConnection::readMessages( SocketMonitor& s )
{
  if( !m_pSession ) return;

  std::string msg;
  while( readMessage( msg ) )
  {
    try
    {
      m_pSession->next( msg, UtcTimeStamp() );
    }
    catch ( InvalidMessage& )
    {
      if( !m_pSession->isLoggedOn() )
        s.drop( m_socket );
    }
  }
}

void FqSocketConnection::onTimeout()
{ if ( m_pSession ) m_pSession->next();

}

} // namespace FreeQuant
