#include "FQSocketConnection.h"

using namespace FIX;

namespace FreeQuant {

FQSocketConnection::FQSocketConnection(int s, Sessions sessions, SocketMonitor* pMonitor) :
    SocketConnection(s, sessions, pMonitor) {
}

FQSocketConnection::FQSocketConnection(SocketInitiator& i, const SessionID& sessionID,
    int s, SocketMonitor* pMonitor) : SocketConnection(i, sessionID, s, pMonitor) {

}

} // namespace FreeQuant
