#ifndef FQ_TRADE_TWSTRADEPROVIDER_H
#define FQ_TRADE_TWSTRADEPROVIDER_H

#include <string>
#include <vector>

#include <freequant/trade/TradeProvider.h>
#include <freequant/strategy/Order.h>

#include "EWrapper.h"
#include "EPosixClientSocket.h"

namespace FreeQuant {

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
    void logout();

    void subscribe(std::vector<std::string> symbols);
    void unsubscribe(std::vector<std::string> symbols);

    void sendOrder(FreeQuant::Order& order);
    void cancelOrder(FreeQuant::Order& order);
    void replaceOrder(FreeQuant::Order& order);

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

private:
   std::shared_ptr<EPosixClientSocket> _socket;
   std::vector<std::string> _accoutCodes;
};


}  // namespace FreeQuant

#endif // FQ_TRADE_TWSTRADEPROVIDER_H
