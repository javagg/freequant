#include <iostream>
#include <string>

#include "twsprovider.h"
#include "EWrapper.h"
#include "EPosixClientSocket.h"
#include "Contract.h"

using namespace std;

namespace FreeQuant { namespace MarketData {

class TwsEWrapper : public EWrapper {
public:
    static int ticker;
    TwsEWrapper() {
        socket = new EPosixClientSocket(this);
    }
    virtual ~TwsEWrapper() {
        delete socket;
    }

    void connect() {
        bool ret = socket->eConnect("127.0.0.1", 7496, 0);
        if (ret) {
            std::cout << "Connected" << std::endl;
        }
    }

    void disconnect() {
        socket->eDisconnect();
        std::cout <<  "Disconnected" << std::endl;
    }

    bool isConnected() const {
        return socket->isConnected();
    }
    void subscribe(std::vector<std::string> symbols) {
        m_tickerId = ticker++;
        Contract contract;
        contract.symbol = "MSFT";
        contract.secType = "STK";
        contract.exchange = "SMART";
        contract.currency = "USD";
        const IBString genericTicks ="100;101;104";
        cout << contract.symbol << endl;
        socket->reqMktData(m_tickerId, contract, genericTicks, false);
    }

    void unsubscribe(std::vector<std::string> symbols) {
        socket->cancelMktData(m_tickerId);
    }

    void currentTime() const {
        socket->reqCurrentTime();
    }

    void reqHistoricalData() {
//         socket->reqHistoricalData();
    }

    void reqFundamentalData(std::string symbol) {
//        socket->reqFundamentalData();
    }

    virtual void tickPrice(TickerId tickerId, TickType field, double price, int canAutoExecute) {

    }
    virtual void tickSize(TickerId tickerId, TickType field, int size){}
    virtual void tickOptionComputation( TickerId tickerId, TickType tickType, double impliedVol, double delta,
        double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice) {}
    virtual void tickGeneric(TickerId tickerId, TickType tickType, double value){}
    virtual void tickString(TickerId tickerId, TickType tickType, const IBString& value) {}
    virtual void tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const IBString& formattedBasisPoints,
        double totalDividends, int holdDays, const IBString& futureExpiry, double dividendImpact, double dividendsToExpiry){}
    virtual void orderStatus( OrderId orderId, const IBString &status, int filled,
        int remaining, double avgFillPrice, int permId, int parentId,
        double lastFillPrice, int clientId, const IBString& whyHeld){}
    virtual void openOrder( OrderId orderId, const Contract&, const Order&, const OrderState&){}
    virtual void openOrderEnd(){}
    virtual void winError( const IBString &str, int lastError){}
    virtual void connectionClosed(){}
    virtual void updateAccountValue(const IBString& key, const IBString& val,
    const IBString& currency, const IBString& accountName){}
    virtual void updatePortfolio( const Contract& contract, int position,
       double marketPrice, double marketValue, double averageCost,
       double unrealizedPNL, double realizedPNL, const IBString& accountName){}
    virtual void updateAccountTime(const IBString& timeStamp){}
    virtual void accountDownloadEnd(const IBString& accountName){}
    virtual void nextValidId( OrderId orderId){}
    virtual void contractDetails( int reqId, const ContractDetails& contractDetails){}
    virtual void bondContractDetails( int reqId, const ContractDetails& contractDetails) {}
    virtual void contractDetailsEnd( int reqId) {}
    virtual void execDetails( int reqId, const Contract& contract, const Execution& execution){}
    virtual void execDetailsEnd( int reqId) {}
    virtual void error(const int id, const int errorCode, const IBString errorString) {
        std::cout << errorString << std::endl;
    }
    virtual void updateMktDepth(TickerId id, int position, int operation, int side,
       double price, int size){}
    virtual void updateMktDepthL2(TickerId id, int position, IBString marketMaker, int operation,
       int side, double price, int size){}
    virtual void updateNewsBulletin(int msgId, int msgType, const IBString& newsMessage, const IBString& originExch) {}
    virtual void managedAccounts( const IBString& accountsList){}
    virtual void receiveFA(faDataType pFaDataType, const IBString& cxml){}
    virtual void historicalData(TickerId reqId, const IBString& date, double open, double high,
        double low, double close, int volume, int barCount, double WAP, int hasGaps){}
    virtual void scannerParameters(const IBString &xml) {}
    virtual void scannerData(int reqId, int rank, const ContractDetails &contractDetails,
        const IBString &distance, const IBString &benchmark, const IBString &projection,
        const IBString &legsStr) {}
    virtual void scannerDataEnd(int reqId) {}
    virtual void realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
        long volume, double wap, int count) {}
    virtual void currentTime(long time) {
        cout << "server time" << time << endl;
//        if ( m_state == ST_PING_ACK) {
//            time_t t = ( time_t)time;
//            struct tm * timeinfo = localtime ( &t);
//            printf( "The current date/time is: %s", asctime( timeinfo));

//            time_t now = ::time(NULL);
//            m_sleepDeadline = now + SLEEP_BETWEEN_PINGS;

//            m_state = ST_IDLE;
//        }
    }
    virtual void fundamentalData(TickerId reqId, const IBString& data) {}
    virtual void deltaNeutralValidation(int reqId, const UnderComp& underComp){}
    virtual void tickSnapshotEnd( int reqId){}
    virtual void marketDataType( TickerId reqId, int marketDataType){}
private:
    EPosixClientSocket *socket;
    TickerId m_tickerId;
};

int TwsEWrapper::ticker = 0;

TwsProvider::TwsProvider() {
    wrapper = new TwsEWrapper();
}

TwsProvider::~TwsProvider() {
    delete wrapper;
}

void TwsProvider::connect(bool block) {
    wrapper->connect();
}

void TwsProvider::disconnect(bool block) {
    wrapper->disconnect();
}

bool TwsProvider::isConnected() const {
    return wrapper->isConnected();
}

void TwsProvider::subscribe(vector<string> symbols) {
    wrapper->subscribe(symbols);
}

void TwsProvider::unsubscribe(vector<string> symbols) {
    wrapper->unsubscribe(symbols);
}

void TwsProvider::currentTime() const {
    wrapper->currentTime();
}

void TwsProvider::reqHistoricalData(FreeQuant::Utils::DateTime startTime, FreeQuant::Utils::DateTime endTime) {
    wrapper->reqHistoricalData();
}

void TwsProvider::reqFundamentalData(string symbol) {
    wrapper->reqFundamentalData(symbol);
}

}}
