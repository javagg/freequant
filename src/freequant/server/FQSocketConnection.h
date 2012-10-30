#ifndef FQ_SERVER_FQSocketConnection_H
#define FQ_SERVER_FQSocketConnection_H

#include <quickfix/SessionID.h>
#include <quickfix/SocketAcceptor.h>
#include <quickfix/SocketServer.h>
#include <quickfix/SocketConnection.h>
#include <quickfix/SocketInitiator.h>
#include <quickfix/SocketMonitor.h>

namespace FreeQuant {

class FQSocketConnection : public FIX::SocketConnection {
public:
    FQSocketConnection(int s, Sessions sessions, FIX::SocketMonitor* pMonitor);
    FQSocketConnection(FIX::SocketInitiator&, const FIX::SessionID&, int, FIX::SocketMonitor*);
};

} // namespace FreeQuant

#endif // FQ_SERVER_FQSocketConnection_H
