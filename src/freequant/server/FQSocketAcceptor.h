#ifndef FQ_SERVER_DynamicSessionSocketAcceptor_H
#define FQ_SERVER_DynamicSessionSocketAcceptor_H

#include <boost/scoped_ptr.hpp>
#include <quickfix/SocketAcceptor.h>
#include <quickfix/SocketServer.h>
#include <quickfix/SocketConnection.h>

//#include <freequant/server/FQSocketConnection.h>

namespace FreeQuant {

class FqSocketConnection;

class FqSocketAcceptor : public FIX::Acceptor, FIX::SocketServer::Strategy {
public:
    FqSocketAcceptor(FIX::Application&, FIX::MessageStoreFactory&,
        const FIX::SessionSettings&) throw(FIX::ConfigError);
    FqSocketAcceptor( FIX::Application&, FIX::MessageStoreFactory&,
        const FIX::SessionSettings&, FIX::LogFactory&) throw(FIX::ConfigError);
    virtual ~FqSocketAcceptor();

    // We have to reimplement all the public functions in order to add a feature.
    void start() throw (FIX::ConfigError, FIX::RuntimeError);
    void block() throw (FIX::ConfigError, FIX::RuntimeError);
    bool poll(double timeout = 0.0) throw (FIX::ConfigError, FIX::RuntimeError);
    void stop(bool force = false);
    bool isLoggedOn();
    FIX::Session *getSession(const std::string&, FIX::Responder&);
    const std::set<FIX::SessionID>& getSessions() const;
    FIX::Session *getSession(const FIX::SessionID&) const;
    const FIX::Dictionary* const getSessionSettings(const FIX::SessionID&) const;
    bool has(const FIX::SessionID&);


private:
    void initialize() throw (FIX::ConfigError);

    bool readSettings(const FIX::SessionSettings&);

    typedef std::set<FIX::SessionID> SessionIDs;
    typedef std::map<FIX::SessionID, FIX::Session*> Sessions;

    typedef std::map<int, SessionIDs> PortToSessions;
    typedef std::map<int, FqSocketConnection*> SocketConnections;

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

    Sessions m_sessions;
    SessionIDs m_sessionIDs;
    FIX::LogFactory* m_pLogFactory;
    FIX::SessionSettings m_settings;
};

} // namespace FreeQuant

#endif // FQ_SERVER_DynamicSessionSocketAcceptor_H
