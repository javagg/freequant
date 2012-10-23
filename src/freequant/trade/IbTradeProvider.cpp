#include <boost/algorithm/string.hpp>
#include <boost/scoped_ptr.hpp>
#include "IbTradeProvider.h"

#include "EWrapper.h"
#include "EPosixClientSocket.h"
#include "Order.h"
#include "Contract.h"

namespace FreeQuant {

class IbTradeProvider::Impl : public EWrapper {
public:
    Impl(FreeQuant::TradeProvider::Callback *callback) :
        _socket(new EPosixClientSocket(this)),
        _callback(callback) {

    }

    ~Impl() {}

    void connect() {

    }

    void disconnect() {

    }

    bool isConnected() const {

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

    virtual void tickPrice( TickerId tickerId, TickType field, double price, int canAutoExecute) {}
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
    virtual void winError( const IBString &str, int lastError) {}
    virtual void connectionClosed()  {}
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
    virtual void error(const int id, const int errorCode, const IBString errorString) {}
    virtual void updateMktDepth(TickerId id, int position, int operation, int side,
       double price, int size) {}
    virtual void updateMktDepthL2(TickerId id, int position, IBString marketMaker, int operation,
       int side, double price, int size)  {}
    virtual void updateNewsBulletin(int msgId, int msgType, const IBString& newsMessage, const IBString& originExch) {}
    virtual void managedAccounts( const IBString& accountsList)  {
        std::vector<std::string> accounts;
        boost::split(accounts, accountsList, boost::is_any_of(","), boost::token_compress_on); // SplitVec == { "hello abc","ABC","aBc goodbye" }
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
    virtual void currentTime(long time) {}
    virtual void fundamentalData(TickerId reqId, const IBString& data) {}
    virtual void deltaNeutralValidation(int reqId, const UnderComp& underComp) {}
    virtual void tickSnapshotEnd( int reqId) {}
    virtual void marketDataType( TickerId reqId, int marketDataType)  {}
    boost::scoped_ptr<EPosixClientSocket> _socket;
    std::vector<std::string> _accoutCodes;
    FreeQuant::TradeProvider::Callback *_callback;
};

void IbTradeProvider::connect() {

}

void IbTradeProvider::disconnect() {

}

bool IbTradeProvider::isConnected() const {

}

IbTradeProvider::IbTradeProvider(FreeQuant::TradeProvider::Callback *callback) :
   _impl(new IbTradeProvider::Impl(callback)) {

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
