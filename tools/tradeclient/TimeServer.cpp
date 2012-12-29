#include <ctime>
#include <iostream>
#include <string>

#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class SocketConnection : public boost::enable_shared_from_this<SocketConnection> {
public:
  typedef boost::shared_ptr<SocketConnection> pointer;

  static pointer create(boost::asio::io_service& io_service)
  {
    return pointer(new SocketConnection(io_service));
  }

  boost::asio::ip::tcp::socket& socket() {
    return _socket;
  }

  void start() {
      time_t now = time(0);
      message_ = std::string(ctime(&now));

      _socket.async_read_some(boost::asio::buffer(_data, _data.size()),
         boost::bind(&SocketConnection::handleRead, shared_from_this(), boost::asio::placeholders::error,
         boost::asio::placeholders::bytes_transferred));
  }

  void stop() {
    _socket.close();
  }

  void handleRead(const boost::system::error_code& error, size_t transferred) {
      if (!error) {

          //            _parser.addToStream(_data.data(), transferred);

          //            std::string message;
              //        if (!_session) {
          //                if (!readMessage(message)) {
              //                _session = FIX::Session::lookupSession(message, true);
              //                if (!_session) {
              //                   FIX::Message fixMessage;
              //                   if (fixMessage.setStringHeader(message)) {
              //                       const FIX::Header& header = fixMessage.getHeader();
              //                       const FIX::BeginString& beginString = FIELD_GET_REF(header, BeginString );
              //                       const FIX::SenderCompID& senderCompID = FIELD_GET_REF(header, SenderCompID );
              //                       const FIX::TargetCompID& targetCompID = FIELD_GET_REF(header, TargetCompID );

              //                       FIX::SessionID sessionID(beginString, FIX::SenderCompID(targetCompID), FIX::TargetCompID( senderCompID));
              //                       if (_callback) _callback->onNewSession(sessionID);
              ////                           new Session(application, MessageStoreFactory&,
              ////                                    const SessionID&,
              ////                                    const DataDictionaryProvider&,
              ////                                    const TimeRange&,
              ////                                    int heartBtInt, LogFactory* pLogFactory );
              //                       _session = FIX::Session::lookupSession(message, true);
              //                   }
              //                }

              //                if (_session) {
              //                    FIX::Session::registerSession(_session->getSessionID());
          //                    }
          //                }
              //        }

//          readMessages();

          std::cout << _data.data() << std::endl;
          _socket.async_read_some(boost::asio::buffer(_data, _data.size()),
              boost::bind(&SocketConnection::handleRead, shared_from_this(), boost::asio::placeholders::error,
              boost::asio::placeholders::bytes_transferred));
      } else if (error != boost::asio::error::operation_aborted) {
          stop();
          std::cout << error.message() << std::endl;
      }
  }
private:
  SocketConnection(boost::asio::io_service& io_service) : _socket(io_service) {}

  void handle_write(const boost::system::error_code& /*error*/,
      size_t /*bytes_transferred*/)
  {
  }

  tcp::socket _socket;
  boost::array<char, 4096> _data;
  std::string message_;
};

class SocketAcceptor
{
public:
    SocketAcceptor() : _io_service(), _acceptor(_io_service), _signals(_io_service) {
        _signals.add(SIGINT);
        _signals.add(SIGTERM);
//        _signals.async_wait(boost::bind(&server::handle_stop, this));
    }

void start() {
    using namespace boost::asio;
    ip::tcp::endpoint endpoint(ip::tcp::v4(), 7714);
    _acceptor.open(endpoint.protocol());
    _acceptor.set_option(ip::tcp::acceptor::reuse_address(true));
    _acceptor.bind(endpoint);
    _acceptor.listen();
    accept();
    _io_service.run();
}

private:
  void accept() {
    SocketConnection::pointer new_connection =
      SocketConnection::create(_acceptor.get_io_service());

    _acceptor.async_accept(new_connection->socket(),[=](const boost::system::error_code& error) {
            if (!error)
            {
              new_connection->start();
            }

            this->accept();
    });
  }

private:
    boost::asio::io_service _io_service;
    boost::asio::signal_set _signals;
    boost::asio::ip::tcp::acceptor _acceptor;
};

int main()
{
  try
  {
    SocketAcceptor server;
    server.start();
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
