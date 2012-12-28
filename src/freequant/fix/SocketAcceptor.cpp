#include "SocketAcceptor.h"
#include "SocketConnection.h"

#include <boost/thread.hpp>

//TODO: remove this line!
#include <quickfix/HttpServer.h>

using namespace FIX;
using namespace boost::asio;

namespace FreeQuant {
SocketAcceptor::SocketAcceptor(FIX::Application& application, FIX::MessageStoreFactory& factory,
    const FIX::SessionSettings& settings, FIX::LogFactory& logFactory) throw(FIX::ConfigError) :
    _application(application), _factory(factory), _settings(settings), _logFactory(&logFactory),
    _io_service(), _acceptor(_io_service), _signals(_io_service) {
    _signals.add(SIGINT);
    _signals.add(SIGTERM);
//        _signals.async_wait(boost::bind(&server::handle_stop, this));
}

SocketAcceptor::~SocketAcceptor() {}

void SocketAcceptor::start() {
    m_stop = false;
//    FIX::HttpServer::startGlobal(_settings);

    ip::tcp::endpoint endpoint(ip::tcp::v4(), 7714);
    _acceptor.open(endpoint.protocol());
    _acceptor.set_option(ip::tcp::acceptor::reuse_address(true));
    _acceptor.bind(endpoint);
    _acceptor.listen();
    accept();
    boost::thread thread(boost::bind(&boost::asio::io_service::run, &_io_service));
}

void SocketAcceptor::stop(bool force) {
    if (isStopped()) return;
//    FIX::HttpServer::stopGlobal();
    _acceptor.close();
}

void SocketAcceptor::accept() {
    SocketConnection::Pointer connection = SocketConnection::create(_io_service, _application,
        _factory, _settings, *_logFactory);
    _acceptor.async_accept(connection->socket(),[=](const boost::system::error_code& error) {
        if (!error) {
          connection->start();
        } else {
            std::cout << "Error in " << __FUNCTION__ << ": " << error.message() << std::endl;
        }
        accept();
    });
}

bool SocketAcceptor::isLoggedOn() {
    return false;
}

}
