
#include "SimpleSocketAcceptor.h"

using namespace std;
using namespace FIX;
using namespace boost::asio;
using namespace boost;

namespace FreeQuant {

SimpleSocketAcceptor::SimpleSocketAcceptor(Application& application,
        MessageStoreFactory& factory, const SessionSettings& settings) throw(ConfigError) :
//    Acceptor(application, factory, settings),
    _application(application), _factory(factory), _settings(settings),
    _acceptor(_io_service) {
}

SimpleSocketAcceptor::SimpleSocketAcceptor(Application& application,
        MessageStoreFactory& factory, const SessionSettings& settings, LogFactory& logFactory)
        throw(ConfigError) :
//    Acceptor(application, factory, settings, logFactory),
    _application(application), _factory(factory), _settings(settings), _logFactory(&logFactory),
    m_pLogFactory(&logFactory),
    _acceptor(_io_service) {
}

void SimpleSocketAcceptor::start() throw (FIX::ConfigError, FIX::RuntimeError) {
    _acceptor.open(ip::tcp::v4());
    _acceptor.set_option(ip::tcp::acceptor::reuse_address(true));
    _acceptor.bind(ip::tcp::endpoint(ip::tcp::v4(), 7711));
    _acceptor.listen(10);
    startAccept();
    _io_service.run();
}

void SimpleSocketAcceptor::stop(bool force) {

}

void SimpleSocketAcceptor::startAccept() {
    pendingConnection.reset(new SimpleSocketConnection(_io_service, this));
    ip::tcp::endpoint remote;
    _acceptor.async_accept(pendingConnection->socket(), remote, bind(&SimpleSocketAcceptor::handleAccept,
        this, boost::asio::placeholders::error));
}

void SimpleSocketAcceptor::handleAccept(const boost::system::error_code& error) {
    if (!error) {
        pendingConnection->start();
        SessionID sessionID;
        _connections[sessionID] = pendingConnection;
        startAccept();
    } else {
        cout << "error in " << __FUNCTION__ << ": " << error.message() << endl;
    }
}

} // namespace FreeQuant
