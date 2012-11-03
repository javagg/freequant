#ifndef FQ_SERVER_SimpleSocketConnection_H
#define FQ_SERVER_SimpleSocketConnection_H

#include <boost/scoped_ptr.hpp>
#include <boost/asio.hpp>

#include <quickfix/SocketAcceptor.h>
#include <quickfix/SocketServer.h>

namespace FreeQuant {

class SimpleSocketAcceptor {
public:
    SimpleSocketAcceptor(FIX::Application&, FIX::MessageStoreFactory&,
        const FIX::SessionSettings&) throw(FIX::ConfigError);
    SimpleSocketAcceptor(FIX::Application&, FIX::MessageStoreFactory&,
        const FIX::SessionSettings&, FIX::LogFactory&) throw(FIX::ConfigError);
    virtual ~SimpleSocketAcceptor() {}

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

    class Connection;
private:
    typedef std::set<FIX::SessionID> SessionIDs;
    typedef std::map<FIX::SessionID, FIX::Session*> Sessions;

    typedef boost::shared_ptr<Connection> ConnectionPtr;
    typedef std::map<FIX::SessionID, ConnectionPtr> Connections;

    void initialize();
    void onConfigure(const FIX::SessionSettings&) throw (FIX::ConfigError) {}
    void onInitialize(const FIX::SessionSettings&) throw (FIX::RuntimeError) {}
    void startAccept();
    void handleAccept(const boost::system::error_code& error);
    void onStart() {}
    bool onPoll( double timeout ) {}
    void onStop() {}

    void onConnect(FIX::SocketServer&, int, int ) {}
    void onWrite(FIX::SocketServer&, int ) {}
    bool onData(FIX::SocketServer&, int ) {}
    void onDisconnect(FIX::SocketServer&, int ) {}
    void onError(FIX::SocketServer& ) {}
    void onTimeout(FIX::SocketServer& ) {}

    SessionIDs _sessionIDs;
    Sessions _sessions;
    FIX::LogFactory* m_pLogFactory;

private:
    Connections _connections;
    ConnectionPtr pendingConnection;

    FIX::Application& _application;
    FIX::MessageStoreFactory& _factory;
    const FIX::SessionSettings& _settings;
    FIX::LogFactory* _logFactory;

    boost::asio::io_service _io_service;
    boost::asio::ip::tcp::acceptor _acceptor;
};

} // namespace FreeQuant

#endif // FQ_SERVER_SimpleSocketConnection_H
