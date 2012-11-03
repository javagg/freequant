#ifndef FQ_SERVER_SimpleSocketConnection_H
#define FQ_SERVER_SimpleSocketConnection_H

#include <string>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/asio.hpp>

#include <quickfix/SocketAcceptor.h>
#include <quickfix/SocketServer.h>

#include <quickfix/Session.h>

namespace FreeQuant {

class SimpleSocketConnection : public FIX::Responder {
public:
    class Callback {
    public:
        virtual ~Callback() {}
        virtual void onNewSession(const FIX::SessionID& sessionID) = 0;
    };

    SimpleSocketConnection(boost::asio::io_service& io_service, Callback *callback) :
        _socket(io_service), _callback(callback) {
    }
    ~SimpleSocketConnection() {}

    boost::asio::ip::tcp::socket& socket() {
      return _socket;
    }

    void start() {
        _socket.async_read_some(boost::asio::buffer(_data, _data.size()),
            boost::bind(&SimpleSocketConnection::handleRead, this, boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }

    bool send(const std::string& message) {
        _socket.async_send(boost::asio::buffer(message), 0, boost::bind(&SimpleSocketConnection::handleWrite, this,
            boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }

    void disconnect() {

    }

private:
    void handleRead(const boost::system::error_code& error, size_t transferred) {
        if (!error) {
            std::cout << _data.data() << std::endl;
            _parser.addToStream(_data.data(), transferred);

            std::string message;
            if (!_session) {
                if (!readMessage(message)) {
                    _session = FIX::Session::lookupSession(message, true);
                    if (!_session) {
                       FIX::Message fixMessage;
                       if (fixMessage.setStringHeader(message)) {
                           const FIX::Header& header = fixMessage.getHeader();
                           const FIX::BeginString& beginString = FIELD_GET_REF(header, BeginString );
                           const FIX::SenderCompID& senderCompID = FIELD_GET_REF(header, SenderCompID );
                           const FIX::TargetCompID& targetCompID = FIELD_GET_REF(header, TargetCompID );

                           FIX::SessionID sessionID(beginString, FIX::SenderCompID(targetCompID), FIX::TargetCompID( senderCompID));
                           if (_callback) _callback->onNewSession(sessionID);
//                           new Session(application, MessageStoreFactory&,
//                                    const SessionID&,
//                                    const DataDictionaryProvider&,
//                                    const TimeRange&,
//                                    int heartBtInt, LogFactory* pLogFactory );
                           _session = FIX::Session::lookupSession(message, true);
                       }
                    }

                    if (_session) {
                        FIX::Session::registerSession(_session->getSessionID());
                    }
                }
            }

            readMessages();
            _socket.async_read_some(boost::asio::buffer(_data, _data.size()),
                boost::bind(&SimpleSocketConnection::handleRead, this, boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
        } else {
            std::cout << error.message() << std::endl;
        }
    }

    void handleWrite(const boost::system::error_code& error, size_t bytes_transferred) {
        if (error) {
//            close();
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

    bool readMessage(std::string& message) {
        try {
            return _parser.readFixMessage(message);
        } catch (FIX::MessageParseError&) {}
        return true;
    }

    void readMessages() {
        std::string message;
        while (readMessage(message)) {
            try {
                _session->next(message, FIX::UtcTimeStamp());
            } catch (FIX::InvalidMessage&) {
                if (!_session->isLoggedOn()) {
                }
            }
        }
    }

    Callback *_callback;
    boost::asio::ip::tcp::socket _socket;
    boost::array<char, 4096> _data;
    FIX::Parser _parser;
    FIX::Session *_session;
};

class SimpleSocketAcceptor : public SimpleSocketConnection::Callback {
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

private:
    typedef std::set<FIX::SessionID> SessionIDs;
    typedef std::map<FIX::SessionID, FIX::Session*> Sessions;

    typedef boost::shared_ptr<SimpleSocketConnection> ConnectionPtr;
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

    void onNewSession(const FIX::SessionID &sessionID) {

    }

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
