#ifndef FQ_FIX_SOCKETACCEPTOR_H
#define FQ_FIX_SOCKETACCEPTOR_H

#include <boost/asio.hpp>
#include <quickfix/Application.h>
#include <quickfix/MessageStore.h>
#include <quickfix/SessionSettings.h>
#include <quickfix/Log.h>

namespace FreeQuant {

class SocketAcceptor {
public:
    SocketAcceptor(FIX::Application&, FIX::MessageStoreFactory&,
        const FIX::SessionSettings&, FIX::LogFactory&) throw(FIX::ConfigError);
    virtual ~SocketAcceptor();
    void start();
    void stop(bool force = true);
    bool isStopped() { return m_stop; }

    /// Check to see if any sessions are currently logged on
    /**
     * Check if we have at least one session and that all the sessions are logged on
     * @return false if no session or at least one session is not logged on
     */
    bool isLoggedOn();
private:
    void accept();

    FIX::Application& _application;
    FIX::MessageStoreFactory& _factory;
    FIX::SessionSettings _settings;
    FIX::LogFactory* _logFactory;
    FIX::Log* m_pLog;
    FIX::NullLog m_nullLog;
    bool m_stop;

    boost::asio::io_service _io_service;
    boost::asio::ip::tcp::acceptor _acceptor;
    boost::asio::signal_set _signals;
};

}

#endif // FQ_FIX_SOCKETACCEPTOR_H
