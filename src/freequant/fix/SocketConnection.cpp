#include "SocketConnection.h"

#include <boost/bind.hpp>

#include <quickfix/SessionFactory.h>

using namespace FIX;

namespace FreeQuant {

SocketConnection::SocketConnection(boost::asio::io_service& io_service, FIX::Application& application,
    FIX::MessageStoreFactory& messageStoreFactory, const FIX::SessionSettings& settings, FIX::LogFactory& logFactory) :
    _application(application), _messageStoreFactory(messageStoreFactory), _settings(settings), _logFactory(logFactory),
    _socket(io_service), _session(nullptr)
{}

SocketConnection::Pointer SocketConnection::create(boost::asio::io_service& io_service,  FIX::Application& application,
    FIX::MessageStoreFactory& messageStoreFactory, const FIX::SessionSettings& settings, FIX::LogFactory& logFactory) {
    return Pointer(new SocketConnection(io_service, application, messageStoreFactory, settings, logFactory));
}

boost::asio::ip::tcp::socket& SocketConnection::socket() {
    return _socket;
}

void SocketConnection::start() {
    _socket.async_read_some(boost::asio::buffer(_data, _data.size()),
        boost::bind(&SocketConnection::handleRead, shared_from_this(), boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

void SocketConnection::stop() {
    _socket.close();
}

bool SocketConnection::readMessage(std::string& message) {
    bool valid = false;
    try {
        valid = _parser.readFixMessage(message);
    } catch (MessageParseError&) {}
    return valid;
}

SessionID SocketConnection::createSessionIDFromMessage(const std::string& str) {
    FIX::Message message;
    if (!message.setStringHeader(str)) return SessionID();
    BeginString beginString;
    SenderCompID clSenderCompID;
    TargetCompID clTargetCompID;
    FIX::MsgType msgType;
    try {
        message.getHeader().getField(beginString);
        message.getHeader().getField(clSenderCompID);
        message.getHeader().getField(clTargetCompID);
        message.getHeader().getField(msgType);
        SenderCompID senderCompID(clTargetCompID);
        TargetCompID targetCompID(clSenderCompID);
        return SessionID(beginString, senderCompID, targetCompID);
    }
    catch (FieldNotFound&) { return SessionID(); }
}

void SocketConnection::handleRead(const boost::system::error_code& error, size_t transferred) {
    if (!error) {
        _parser.addToStream(_data.data(), transferred);

        std::string message;
        while (readMessage(message)) {
            // Check whether this connection is associated with a session object;
            if (!_session) {
                _session = Session::lookupSession(message, true);
                if (!_session) {
                    SessionID sessionID = this->createSessionIDFromMessage(message);
                    SessionFactory factory(_application, _messageStoreFactory, &_logFactory);
                    try {
                        _session = factory.create(sessionID, _settings.get());
                        _session->setResponder(this);
                    } catch (const FIX::ConfigError&) {}
                }
                Session::registerSession(_session->getSessionID());
            }

            try {
                _session->next(message, UtcTimeStamp());
            } catch (InvalidMessage&) {}
        }

      _socket.async_read_some(boost::asio::buffer(_data, _data.size()),
          boost::bind(&SocketConnection::handleRead, shared_from_this(), boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  } else if (error != boost::asio::error::operation_aborted) {
      stop();
      std::cout << "Error in " << __FUNCTION__ << ": " << error.message() << std::endl;
  }
}

void SocketConnection::handle_write(const boost::system::error_code& /*error*/,
  size_t /*bytes_transferred*/)
{
}
// FIX::Responder methods
bool SocketConnection::send(const std::string& message) {
//    _socket.async_send(boost::asio::buffer(message),
//        boost::bind(&SocketConnection::handle_write, shared_from_this(),
//          boost::asio::placeholders::error,
//          boost::asio::placeholders::bytes_transferred));
    return _socket.send(boost::asio::buffer(message));
}

void SocketConnection::disconnect() {

}

}
