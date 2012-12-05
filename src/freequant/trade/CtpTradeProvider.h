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
    virtual void connect(const std::string& connection, bool block = false);
    virtual void disconnect();
    virtual bool isConnected() const;
    virtual std::string name() const { return "CTP"; }

    virtual std::vector<std::string> availableExchanges() const;
    virtual std::vector<std::string> availableInstruments() const;

    void sendOrder(const FreeQuant::Order& order);
    void cancelOrder(const FreeQuant::Order& order);
    void replaceOrder(const FreeQuant::Order& order);

    void updateAccount(bool block = false);
    void updateAccounts();
    void updatePosition(const std::string& symbol);
    void openOrders() const;

    void fetchOrders(const std::string& symbol, const DateTime& start, const DateTime& end);
    void fetchTrades(const std::string& symbol, const DateTime& start, const DateTime& end);

    void updateIntrument(const std::string& symbol, bool block = false);
    void updateIntrument(FreeQuant::Instrument& instrument) {}

    bool orderTypeSupported(FreeQuant::Order::OrderType type) { return true; }
private:
    class Impl;
    std::unique_ptr<Impl> _impl;
};

} // namespace FreeQuant

#endif // FQ_TRADE_CTPTRADEPROVIDER_H
