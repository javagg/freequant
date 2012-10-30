#ifndef FQ_SERVER_FQSocketConnection_H
#define FQ_SERVER_FQSocketConnection_H

#include <quickfix/SessionID.h>
#include <quickfix/SocketAcceptor.h>
#include <quickfix/SocketServer.h>
#include <quickfix/SocketConnection.h>
#include <quickfix/SocketInitiator.h>
#include <quickfix/SocketMonitor.h>
#include <freequant/server/DynamicSessionSocketAcceptor.h>

namespace FIX {

}
namespace FreeQuant {

class FQSocketConnection : FIX::Responder {
public:

      typedef std::set<FIX::SessionID> Sessions;
    FQSocketConnection(int s, Sessions sessions, FIX::SocketMonitor* pMonitor);
    FQSocketConnection(FIX::SocketInitiator&, const FIX::SessionID&, int, FIX::SocketMonitor*);
    virtual ~FQSocketConnection();

    int getSocket() const { return m_socket; }
    FIX::Session* getSession() const { return m_pSession; }

    bool read(FIX::SocketConnector& s );
    bool read(FreeQuant::DynamicSessionSocketAcceptor&, FIX::SocketServer& );
    bool processQueue();

    void signal()
    {
      FIX::Locker l( m_mutex );
      if( m_sendQueue.size() == 1 )
        m_pMonitor->signal( m_socket );
    }

    void unsignal()
    {
      FIX::Locker l( m_mutex );
      if( m_sendQueue.size() == 0 )
        m_pMonitor->unsignal( m_socket );
    }

    void onTimeout();

  private:
    typedef std::deque<std::string, ALLOCATOR<std::string> >
      Queue;

    bool isValidSession();
    void readFromSocket() throw(FIX::SocketRecvFailed );
    bool readMessage( std::string& msg );
    void readMessages(FIX::SocketMonitor& s );
    bool send( const std::string& );
    void disconnect();

    int m_socket;
    char m_buffer[BUFSIZ];

    FIX::Parser m_parser;
    Queue m_sendQueue;
    unsigned m_sendLength;
    Sessions m_sessions;
    FIX::Session* m_pSession;
    FIX::SocketMonitor* m_pMonitor;
    FIX::Mutex m_mutex;
    fd_set m_fds;
};

} // namespace FreeQuant

#endif // FQ_SERVER_FQSocketConnection_H
