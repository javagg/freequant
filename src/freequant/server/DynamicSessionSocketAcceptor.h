#ifndef FQ_SERVER_DynamicSessionSocketAcceptor_H
#define FQ_SERVER_DynamicSessionSocketAcceptor_H

#include <boost/scoped_ptr.hpp>
#include <quickfix/SocketAcceptor.h>
#include <quickfix/SocketServer.h>
#include <quickfix/SocketConnection.h>

//#include <freequant/server/FQSocketConnection.h>

namespace FreeQuant {

class FQSocketConnection;

class DynamicSessionSocketAcceptor : public FIX::Acceptor, FIX::SocketServer::Strategy {
public:
    DynamicSessionSocketAcceptor(FIX::Application&, FIX::MessageStoreFactory&,
        const FIX::SessionSettings&) throw(FIX::ConfigError);
    DynamicSessionSocketAcceptor( FIX::Application&, FIX::MessageStoreFactory&,
        const FIX::SessionSettings&, FIX::LogFactory&) throw(FIX::ConfigError);
    virtual ~DynamicSessionSocketAcceptor();

private:
    bool readSettings(const FIX::SessionSettings&);

    typedef std::set<FIX::SessionID> Sessions;
    typedef std::map<int, Sessions> PortToSessions;
    typedef std::map<int, FQSocketConnection*> SocketConnections;

    void onConfigure(const FIX::SessionSettings&) throw (FIX::ConfigError );
    void onInitialize(const FIX::SessionSettings&) throw (FIX::RuntimeError );

    void onStart();
    bool onPoll( double timeout );
    void onStop();

    void onConnect(FIX::SocketServer&, int, int );
    void onWrite(FIX::SocketServer&, int );
    bool onData(FIX::SocketServer&, int );
    void onDisconnect(FIX::SocketServer&, int );
    void onError(FIX::SocketServer& );
    void onTimeout(FIX::SocketServer& );

    boost::scoped_ptr<FIX::SocketServer> _server;
    PortToSessions m_portToSessions;
    SocketConnections _connections;
};

} // namespace FreeQuant

#endif // FQ_SERVER_DynamicSessionSocketAcceptor_H
