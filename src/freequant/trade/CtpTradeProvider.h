#ifndef FQ_TRADE_CTPTRADEPROVIDER_H
#define FQ_TRADE_CTPTRADEPROVIDER_H

#include <memory>

#include <freequant/trade/TradeProvider.h>

namespace FreeQuant {

class CtpTradeProvider : public TradeProvider {
public:
    explicit CtpTradeProvider(const std::string& connection, FreeQuant::TradeProvider::Callback *callback = 0);
    virtual ~CtpTradeProvider();
    virtual void connect();
    virtual void disconnect();
    virtual bool isConnected() const;
    virtual std::string name() const { return "CTP"; }

    virtual std::vector<std::string> availableExchanges() const;
    virtual std::vector<std::string> availableInstruments() const;

    void sendOrder(FreeQuant::Order& order);
    void cancelOrder(FreeQuant::Order& order);
    void replaceOrder(FreeQuant::Order& order);

    void updateAccounts();
    void updatePosition(std::string symbol);
    void openOrders() const;

    void updateIntrument(std::string symbol, bool block = false);
    void updateIntrument(FreeQuant::Instrument& instrument) {}

    bool orderTypeSupported(FreeQuant::Order::Type type) { return true; }
private:
    class Impl;
    std::unique_ptr<Impl> _impl;
};

} // namespace FreeQuant

#endif // FQ_TRADE_CTPTRADEPROVIDER_H
