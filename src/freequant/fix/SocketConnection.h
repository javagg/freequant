#ifndef FQ_FIX_SOCKETCONNECTION_H
#define FQ_FIX_SOCKETCONNECTION_H

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <quickfix/Parser.h>
#include <quickfix/Session.h>

namespace FreeQuant {

class SocketConnection : public FIX::Responder, public boost::enable_shared_from_this<SocketConnection> {
public:
    typedef boost::shared_ptr<SocketConnection> Pointer;

    static Pointer create(boost::asio::io_service& io_service, FIX::Application& application,
        FIX::MessageStoreFactory& messageStoreFactory, const FIX::SessionSettings& settings, FIX::LogFactory& logFactory);
    boost::asio::ip::tcp::socket& socket();
    void start();
    void stop();

    // FIX::Responder methods
    bool send(const std::string&);
    void disconnect();
private:
    SocketConnection(boost::asio::io_service& io_service, FIX::Application& application,
        FIX::MessageStoreFactory& messageStoreFactory, const FIX::SessionSettings& settings, FIX::LogFactory& logFactory);
    void handleRead(const boost::system::error_code&, std::size_t);
    void handle_write(const boost::system::error_code&, std::size_t);

    bool readMessage(std::string& message);
    FIX::SessionID createSessionIDFromMessage(const std::string& str);

    boost::asio::ip::tcp::socket _socket;
    boost::array<char, 4096> _data;
    FIX::Parser _parser;
    FIX::Session *_session;

    FIX::Application& _application;
    FIX::MessageStoreFactory& _messageStoreFactory;
    const FIX::SessionSettings& _settings;
    FIX::LogFactory& _logFactory;
};

}

#endif // FQ_FIX_SOCKETCONNECTION_H
