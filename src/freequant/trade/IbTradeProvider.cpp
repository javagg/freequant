#include <boost/algorithm/string.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/thread.hpp>

#include "IbTradeProvider.h"
#include "EWrapper.h"
#include "EPosixClientSocket.h"
#include "Order.h"
#include "Contract.h"


static const int PING_DEADLINE = 2; // seconds
static const int SLEEP_BETWEEN_PINGS = 30; // seconds

static long tickId = 0;

namespace FreeQuant {

class IbTradeProvider::Impl : private EWrapper {
public:
    enum State {
        ST_CONNECT,
        ST_PING,
        ST_PING_ACK,
        ST_IDLE
    };

    Impl(FreeQuant::TradeProvider::Callback *callback) :
        _socket(new EPosixClientSocket(this)),
        _callback(callback),
        _state(ST_CONNECT),
        _sleepDeadline(0) {
    }

    ~Impl() {}

    void connect() {
        bool ret = _socket->eConnect("127.0.0.1", 7496, 0);
        if (ret) {
            std::cout << "--->>> serverVersion: " << _socket->serverVersion() << std::endl
                     << "--->>> TwsConnectionTime: " << _socket-> TwsConnectionTime() << std::endl;
//            _socket->reqCurrentTime();
        }
    }

    void disconnect() {
        _socket->eDisconnect();
    }

    bool isConnected() const {
        return _socket->isConnected();
    }

    std::string name() const { return "TWS"; }

    std::vector<std::string> availableExchanges() const {

    }
    std::vector<std::string> availableInstruments() const {

    }

    std::vector<std::string> availableAccounts() const {
        _socket->reqManagedAccts();
        return std::vector<std::string>();
    }

    void updateAccounts() {

    }

    void logon() {

    }

    void logout() {

    }

    void subscribe(std::vector<std::string> symbols) {

    }

    void unsubscribe(std::vector<std::string> symbols) {

    }

    void sendOrder(FreeQuant::Order& order) {
        OrderId orderId = 111;
        Contract contract;
        ::Order o;
        _socket->placeOrder(orderId, contract, o);
    }

    void cancelOrder(FreeQuant::Order& order) {
        OrderId orderId = 111;
        _socket->cancelOrder(orderId);
    }

    void replaceOrder(FreeQuant::Order& order) {

    }

    void exec() {
        while (isConnected()) {
            processMessages();
        }
    }

    void processMessages() {
        fd_set readSet, writeSet, errorSet;
        struct timeval tval;
        tval.tv_usec = 0;
        tval.tv_sec = 0;

        time_t now = ::time(NULL);

        switch (_state) {
//            case ST_PLACEORDER:
//                placeOrder();
//                break;
//            case ST_PLACEORDER_ACK:
//                break;
//            case ST_CANCELORDER:
//                cancelOrder();
//                break;
//            case ST_CANCELORDER_ACK:
//                break;
            case ST_PING:
                reqCurrentTime();
                break;
            case ST_PING_ACK:
                if (_sleepDeadline < now) {
                    disconnect();
                    return;
                }
                break;
            case ST_IDLE:
                if (_sleepDeadline < now) {
                    _state = ST_PING;
                    return;
                }
                break;
        }

        if (_sleepDeadline > 0) {
            // initialize timeout with m_sleepDeadline - now
            tval.tv_sec = _sleepDeadline - now;
        }

        if (_socket->fd() >= 0) {
            FD_ZERO(&readSet);
            errorSet = writeSet = readSet;

            FD_SET(_socket->fd(), &readSet);

            if (!_socket->isOutBufferEmpty()) {
                FD_SET(_socket->fd(), &writeSet);
            }

            FD_CLR(_socket->fd(), &errorSet);

            int ret = select(_socket->fd() + 1, &readSet, &writeSet, &errorSet, &tval);

            if (ret == 0) { // timeout
                return;
            }

            if (ret < 0) {	// error
                disconnect();
                return;
            }

            if (_socket->fd() < 0) {
                return;
            }

            if (FD_ISSET(_socket->fd(), &errorSet)) {
                    // error on socket
                _socket->onError();
            }

            if (_socket->fd() < 0) {
                return;
            }

            if (FD_ISSET(_socket->fd(), &writeSet)) {
                // socket is ready for writing
                _socket->onSend();
            }

            if (_socket->fd() < 0) {
                    return;
            }

            if (FD_ISSET(_socket->fd(), &readSet)) {
                // socket is ready for reading
                _socket->onReceive();
            }
        }
    }
private:
    void reqCurrentTime() {
        // set ping deadline to "now + n seconds"
        _sleepDeadline = time( NULL) + PING_DEADLINE;
        _state = ST_PING_ACK;
        _socket->reqCurrentTime();
    }

    virtual void tickPrice(TickerId tickerId, TickType field, double price, int canAutoExecute) {}
    virtual void tickSize( TickerId tickerId, TickType field, int size) {}
    virtual void tickOptionComputation( TickerId tickerId, TickType tickType, double impliedVol, double delta,
        double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice) {}
    virtual void tickGeneric(TickerId tickerId, TickType tickType, double value) {}
    virtual void tickString(TickerId tickerId, TickType tickType, const IBString& value) {}
    virtual void tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const IBString& formattedBasisPoints,
        double totalDividends, int holdDays, const IBString& futureExpiry, double dividendImpact, double dividendsToExpiry) {}
    virtual void orderStatus( OrderId orderId, const IBString &status, int filled,
        int remaining, double avgFillPrice, int permId, int parentId,
        double lastFillPrice, int clientId, const IBString& whyHeld) {}

    virtual void openOrder(OrderId orderId, const Contract&, const ::Order&, const OrderState&) {

    }
    virtual void openOrderEnd() {}
    void winError( const IBString &str, int lastError) {
        std::cout << "--->>>" <<__FUNCTION__ << str << std::endl;
    }
    virtual void connectionClosed()  {
        std::cout << "--->>>" <<__FUNCTION__ << std::endl;
    }
    virtual void updateAccountValue(const IBString& key, const IBString& val,
        const IBString& currency, const IBString& accountName)  {
        std::string code = _accoutCodes.front();
        _socket->reqAccountUpdates(true, code);
    }
    virtual void updatePortfolio( const Contract& contract, int position,
       double marketPrice, double marketValue, double averageCost,
       double unrealizedPNL, double realizedPNL, const IBString& accountName) {}
    virtual void updateAccountTime(const IBString& timeStamp)  {}
    virtual void accountDownloadEnd(const IBString& accountName)  {}
    virtual void nextValidId( OrderId orderId)  {}
    virtual void contractDetails( int reqId, const ContractDetails& contractDetails)  {}
    virtual void bondContractDetails( int reqId, const ContractDetails& contractDetails)  {}
    virtual void contractDetailsEnd( int reqId)  {}
    virtual void execDetails( int reqId, const Contract& contract, const Execution& execution) {}
    virtual void execDetailsEnd( int reqId) {}
    void error(const int id, const int errorCode, const IBString errorString) {
        std::cout << errorString << std::endl;
    }
    virtual void updateMktDepth(TickerId id, int position, int operation, int side,
       double price, int size) {}
    virtual void updateMktDepthL2(TickerId id, int position, IBString marketMaker, int operation,
       int side, double price, int size)  {}
    virtual void updateNewsBulletin(int msgId, int msgType, const IBString& newsMessage, const IBString& originExch) {}
    void managedAccounts(const IBString& accountsList)  {
        std::cout << "--->>>" <<__FUNCTION__ << std::endl;
        std::vector<std::string> accounts;
        boost::split(accounts, accountsList, boost::is_any_of(","), boost::token_compress_on);
        std::copy(accounts.begin(), accounts.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
    }
    virtual void receiveFA(faDataType pFaDataType, const IBString& cxml) {}
    virtual void historicalData(TickerId reqId, const IBString& date, double open, double high,
        double low, double close, int volume, int barCount, double WAP, int hasGaps) {}
    virtual void scannerParameters(const IBString &xml) {}
    virtual void scannerData(int reqId, int rank, const ContractDetails &contractDetails,
        const IBString &distance, const IBString &benchmark, const IBString &projection,
        const IBString &legsStr) {}
    virtual void scannerDataEnd(int reqId)  {}
    virtual void realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
        long volume, double wap, int count)  {}

    virtual void currentTime(long time) {
        if (_state == ST_PING_ACK) {
            time_t t = (time_t)time;
            struct tm *timeinfo = localtime(&t);
            std::cout << "The current date/time is: " << asctime(timeinfo) << std::endl;
            time_t now = ::time(NULL);
            _sleepDeadline = now + SLEEP_BETWEEN_PINGS;
            _state = ST_IDLE;
        }
    }
    virtual void fundamentalData(TickerId reqId, const IBString& data) {}
    virtual void deltaNeutralValidation(int reqId, const UnderComp& underComp) {}
    virtual void tickSnapshotEnd( int reqId) {}
    virtual void marketDataType( TickerId reqId, int marketDataType)  {}
    virtual void commissionReport( const CommissionReport &commissionReport) {

    }

    std::auto_ptr<EPosixClientSocket> _socket;
    std::vector<std::string> _accoutCodes;
    FreeQuant::TradeProvider::Callback *_callback;
    State _state;
    time_t _sleepDeadline;
    boost::scoped_ptr<boost::thread> _thread;
};

IbTradeProvider::IbTradeProvider(FreeQuant::TradeProvider::Callback *callback) :
   _impl(new IbTradeProvider::Impl(callback)) {
}

IbTradeProvider::~IbTradeProvider() {
    delete _impl; _impl = 0;
}

void IbTradeProvider::connect() {
    _impl->connect();
}

void IbTradeProvider::disconnect() {
    _impl->disconnect();
}

bool IbTradeProvider::isConnected() const {
    return _impl->isConnected();
}


std::vector<std::string> IbTradeProvider::availableAccounts() const {
    return _impl->availableAccounts();

}

void IbTradeProvider::sendOrder(FreeQuant::Order& order) {

}
void IbTradeProvider::cancelOrder(FreeQuant::Order& order) {

}
void IbTradeProvider::replaceOrder(FreeQuant::Order& order) {
}


}
