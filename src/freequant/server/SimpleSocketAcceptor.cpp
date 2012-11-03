#include <string>
#include <boost/array.hpp>
#include <boost/bind.hpp>

#include "SimpleSocketAcceptor.h"

using namespace std;
using namespace FIX;
using namespace boost::asio;
using namespace boost;

namespace FreeQuant {

class SimpleSocketAcceptor::Connection {
public:
    Connection(boost::asio::io_service& io_service) :
        _socket(io_service) {
    }
    ~Connection() {}

    boost::asio::ip::tcp::socket& socket() {
      return _socket;
    }

    void start() {
        _socket.async_read_some(boost::asio::buffer(_data, _data.size()),
            boost::bind(&Connection::handleRead, this, boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }

    void close() {

    }

private:
    void handleRead(const boost::system::error_code& error, size_t transferred) {
        if (!error) {
            cout << _data.data() << endl;
            _parser.addToStream(_data.data(), transferred);

            _socket.async_read_some(boost::asio::buffer(_data, _data.size()),
                boost::bind(&Connection::handleRead, this, boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
        } else {
            cout << error.message() << endl;
        }
    }

    void handleWrite(const boost::system::error_code& error) {
        if (error) {
            close();
        }
//        if (!error) {
//        socket_.async_read_some(boost::asio::buffer(data_, max_length),
//            boost::bind(&session::handle_read, this,
//              boost::asio::placeholders::error,
//              boost::asio::placeholders::bytes_transferred));
//      }
//      else
//      {
//        delete this;
//      }
    }

    boost::asio::ip::tcp::socket _socket;
    boost::array<char, 4096> _data;
    FIX::Parser _parser;
};

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
    pendingConnection.reset(new Connection(_io_service));
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
