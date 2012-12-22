#ifndef FQ_SERVER_DynamicSessionSocketAcceptor_H
#define FQ_SERVER_DynamicSessionSocketAcceptor_H

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/scoped_ptr.hpp>
#include <quickfix/SocketAcceptor.h>
#include <quickfix/SocketServer.h>
#include <quickfix/SocketConnection.h>

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

    // FIX::SocketServer::Strategy methods
    void onConnect(FIX::SocketServer&, int acceptSocket, int socket);
    void onWrite(FIX::SocketServer&, int socket);
    bool onData(FIX::SocketServer&, int socket);
    void onDisconnect(FIX::SocketServer&, int socket);
    void onError(FIX::SocketServer&);
    void onTimeout(FIX::SocketServer&);

private:
    // We also have to reimplement all the private functions in order to add a feature.
    void onConfigure(const FIX::SessionSettings&) throw (FIX::ConfigError);
    void onInitialize(const FIX::SessionSettings&) throw (FIX::RuntimeError);
    void onStart();
    bool onPoll( double timeout );
    void onStop();

    typedef std::set<FIX::SessionID> SessionIDs;
    typedef std::map<FIX::SessionID, FIX::Session*> Sessions;

    typedef std::map<int, SessionIDs> PortToSessions;
    typedef std::map<int, FqSocketConnection*> SocketConnections;

    bool readSettings(const FIX::SessionSettings&);

    void createSession();
    boost::scoped_ptr<FIX::SocketServer> _server;
    PortToSessions m_portToSessions;
    SocketConnections _connections;

    Sessions m_sessions;
    SessionIDs m_sessionIDs;
    FIX::LogFactory* m_pLogFactory;
    FIX::SessionSettings _settings;
};

class SocketAcceptor : public FIX::SocketServer::Strategy {
public:
    SocketAcceptor(FIX::Application&, FIX::MessageStoreFactory&,
        const FIX::SessionSettings&) throw(FIX::ConfigError);
    SocketAcceptor( FIX::Application&, FIX::MessageStoreFactory&,
        const FIX::SessionSettings&, FIX::LogFactory&) throw(FIX::ConfigError);
    virtual ~SocketAcceptor();

    // We have to reimplement all the public functions in order to add a feature.
    void start() throw (FIX::ConfigError, FIX::RuntimeError);
//    void block() throw (FIX::ConfigError, FIX::RuntimeError);
//    bool poll(double timeout = 0.0) throw (FIX::ConfigError, FIX::RuntimeError);
    void stop(bool force = false);
    bool isStopped();
//    bool isLoggedOn();
//    FIX::Session *getSession(const std::string&, FIX::Responder&);
//    const std::set<FIX::SessionID>& getSessions() const;
//    FIX::Session *getSession(const FIX::SessionID&) const;
//    const FIX::Dictionary* const getSessionSettings(const FIX::SessionID&) const;
//    bool has(const FIX::SessionID&);

    void accept();
    // FIX::SocketServer::Strategy methods
    void onConnect(FIX::SocketServer&, int acceptSocket, int socket);
    void onWrite(FIX::SocketServer&, int socket);
    bool onData(FIX::SocketServer&, int socket);
    void onDisconnect(FIX::SocketServer&, int socket);
    void onError(FIX::SocketServer&);
    void onTimeout(FIX::SocketServer&);
private:
    void initialize();

    // We also have to reimplement all the private functions in order to add a feature.
    void onConfigure(const FIX::SessionSettings&) throw (FIX::ConfigError);
    void onInitialize(const FIX::SessionSettings&) throw (FIX::RuntimeError);
    void onStart();
    bool onPoll(double timeout);
    void onStop();
    typedef std::set<FIX::SessionID> SessionIDs;
    typedef std::map<FIX::SessionID, FIX::Session*> Sessions;

    Sessions m_sessions;
    SessionIDs m_sessionIDs;

    FIX::Application& m_application;
    FIX::MessageStoreFactory& m_messageStoreFactory;
    FIX::SessionSettings m_settings;
    FIX::LogFactory* m_pLogFactory;
    FIX::Log* m_pLog;
    FIX::NullLog m_nullLog;
    bool m_stop;

    boost::asio::io_service _io_service;
    boost::asio::ip::tcp::acceptor _acceptor;

    void handleRead(const boost::system::error_code& error, size_t transferred);
    void handleWrite(const boost::system::error_code& error, size_t bytes_transferred);
    void readMessages();
    bool readMessage(std::string& message);
};

} // namespace FreeQuant

#endif // FQ_SERVER_DynamicSessionSocketAcceptor_H
