#include <boost/algorithm/string.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/thread.hpp>

#include "TwsTradeProvider.h"
#include "EWrapper.h"
#include "EPosixClientSocket.h"
#include "Order.h"
#include "Contract.h"

#include <freequant/strategy/Instrument.h>

#ifdef _WIN32
#  include <Winsock2.h>
#endif

static long tickId = 0;
static long reqId = 0;

namespace FreeQuant {

class TwsTradeProvider::Impl : private EWrapper {
public:
    Impl(FreeQuant::TradeProvider::Callback *callback) :
        _socket(new EPosixClientSocket(this)),
        _callback(callback) {
    }

    ~Impl() {
        delete _socket; _socket = 0;
    }

    void connect() {
        bool ret = _socket->eConnect("127.0.0.1", 7496, 0);
        if (ret) {
            std::cout << "--->>> serverVersion: " << _socket->serverVersion() << std::endl
                     << "--->>> TwsConnectionTime: " << _socket-> TwsConnectionTime() << std::endl;
            _thread.reset(new boost::thread(&Impl::exec, this));
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
        Contract contract;
        contract.symbol = "MSFT";
        contract.secType = "STK";
        contract.exchange = "SMART";
        contract.currency = "USD";
        const IBString genericTicks ="428";
        _socket->reqMktData(0, contract, genericTicks, false);
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

    void updateIntrument(std::string symbol, bool block) {
        Contract contract;
        contract.symbol = symbol;
        _socket->reqContractDetails(reqId++, contract);
    }

    void exec() {
        while (isConnected()) {
            int fd = -1;
            if ((fd = _socket->fd()) < 0)
                return;

            fd_set readSet, writeSet, errorSet;

            FD_ZERO(&readSet);
            FD_ZERO(&writeSet);
            FD_ZERO(&errorSet);

            FD_SET(fd, &readSet);
            if (!_socket->isOutBufferEmpty()) {
                FD_SET(fd, &writeSet);
            }
            FD_CLR(fd, &errorSet);

            int ret = select(fd + 1, &readSet, &writeSet, &errorSet, NULL);
            if (ret < 0) {
                disconnect();
                return;
            }

            if (FD_ISSET(_socket->fd(), &errorSet))
                _socket->onError();

            if (!_socket->isSocketOK())
                return;

            if (FD_ISSET(_socket->fd(), &writeSet))
                _socket->onSend();

            if (!_socket->isSocketOK())
                return;

            if (FD_ISSET(_socket->fd(), &readSet))
                _socket->onReceive();


            if (!_socket->isSocketOK())
                return;
        }
    }

private:
    virtual void tickPrice(TickerId tickerId, TickType field, double price, int canAutoExecute) {
        std::cout << "TickerId:" << tickerId << " TickType: " << field << " price: " << price << std::endl;

    }
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
    virtual void contractDetails(int reqId, const ContractDetails& contractDetails)  {
        std::cout << contractDetails.longName << std::endl;
    }
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
    }
    virtual void fundamentalData(TickerId reqId, const IBString& data) {}
    virtual void deltaNeutralValidation(int reqId, const UnderComp& underComp) {}
    virtual void tickSnapshotEnd( int reqId) {}
    virtual void marketDataType( TickerId reqId, int marketDataType)  {}
    virtual void commissionReport( const CommissionReport &commissionReport) {

    }

    EPosixClientSocket *_socket;
    std::vector<std::string> _accoutCodes;
    FreeQuant::TradeProvider::Callback *_callback;
    boost::scoped_ptr<boost::thread> _thread;
};

TwsTradeProvider::TwsTradeProvider(FreeQuant::TradeProvider::Callback *callback) :
   _impl(new TwsTradeProvider::Impl(callback)) {
}

TwsTradeProvider::~TwsTradeProvider() {
    delete _impl; _impl = 0;
}

void TwsTradeProvider::connect() {
    _impl->connect();
}

void TwsTradeProvider::disconnect() {
    _impl->disconnect();
}

bool TwsTradeProvider::isConnected() const {
    return _impl->isConnected();
}

void TwsTradeProvider::subscribe(std::vector<std::string> symbols) {
    _impl->subscribe(symbols);
}

std::vector<std::string> TwsTradeProvider::availableAccounts() const {
    return _impl->availableAccounts();

}

void TwsTradeProvider::sendOrder(FreeQuant::Order& order) {

}
void TwsTradeProvider::cancelOrder(FreeQuant::Order& order) {

}
void TwsTradeProvider::replaceOrder(FreeQuant::Order& order) {
}

void TwsTradeProvider::updateIntrument(std::string symbol, bool block) {
    _impl->updateIntrument(symbol, block);
}

void TwsTradeProvider::updateIntrument(FreeQuant::Instrument& instrument) {

}

}
