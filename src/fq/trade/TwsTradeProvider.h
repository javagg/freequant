#ifndef FQ_TRADE_TWSTRADEPROVIDER_H
#define FQ_TRADE_TWSTRADEPROVIDER_H

#include <string>
#include <vector>

#include <fq/trade/TradeProvider.h>
#include <fq/strategy/Order.h>

#include "EWrapper.h"
#include "EPosixClientSocket.h"

namespace FreeQuant { namespace Trade {

class HistoricalDataRequest;

class TwsTradeProvider : public TradeProvider, private EWrapper {
public:
    TwsTradeProvider();
    virtual ~TwsTradeProvider();
    void connect();
    void disconnect();
    bool isConnected() const;
    std::string name() const { return "TWS"; }

    std::vector<std::string> availableExchanges() const;
    std::vector<std::string> availableInstruments() const;
    std::vector<std::string> availableAccounts() const;

    void updateAccounts();

    void logon();
    void onLogon();
    void logout();
    void onLogout();
    void onError() {}
    void subscribe(std::vector<std::string> symbols);
    void unsubscribe(std::vector<std::string> symbols);

    void sendOrder(FreeQuant::Strategy::Order& order);
    void cancelOrder(FreeQuant::Strategy::Order& order);
    void replaceOrder(FreeQuant::Strategy::Order& order);
//    void requestHistoricalData(HistoricalDataRequest& request);
//    void cancelHistoricalData(HistoricalDataRequest& request);

private:
    virtual void updateAccountValue(const IBString& key, const IBString& val,
        const IBString& currency, const IBString& accountName);
    virtual void updatePortfolio(const Contract& contract, int position,
       double marketPrice, double marketValue, double averageCost,
       double unrealizedPNL, double realizedPNL, const IBString& accountName);
    virtual void updateAccountTime(const IBString& timeStamp);
    virtual void accountDownloadEnd(const IBString& accountName);
    virtual void managedAccounts(const IBString& accountsList);
//    void onCreate(const FIX::SessionID&);
//    void onLogon(const FIX::SessionID&);
//    void onLogout(const FIX::SessionID&);
//    void toAdmin(FIX::Message&, const FIX::SessionID&);
//    void toApp(FIX::Message&, const FIX::SessionID&)
//        throw(FIX::DoNotSend);
//    void fromAdmin(const FIX::Message&, const FIX::SessionID&)
//        throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon);
//    void fromApp( const FIX::Message&, const FIX::SessionID& )
//        throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType);

//    void onMessage(const FIX44::MarketDataRequestReject&, const FIX::SessionID&);
//    void onMessage(const FIX44::MarketDataIncrementalRefresh&, const FIX::SessionID&);
//    void onMessage(const FIX44::MarketDataSnapshotFullRefresh&, const FIX::SessionID&);
//    void onMessage(const FIX44::ExecutionReport&, const FIX::SessionID&);
//    void onMessage(const FIX44::SecurityList&, const FIX::SessionID&);

//    void sendNewOrderSingle(Order& order);
//    void sendOrderCancelRequest(Order& order);

//    FIX::SessionSettings *m_settings;
//    FIX::FileStoreFactory *m_storeFactory;
//    FIX::SocketInitiator *m_initiator;
//    FIX::SessionID *m_sessionId;

//    std::string senderCompId;
//    std::string targetCompId;
private:
   std::shared_ptr<EPosixClientSocket> _socket;
   std::vector<std::string> _accoutCodes;
};

}}
#endif // FQ_TRADE_TWSTRADEPROVIDER_H
