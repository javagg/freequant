#ifndef FQ_TRADE_FIXTRADEPROVIDER_H
#define FQ_TRADE_FIXTRADEPROVIDER_H

#include <memory>

#include <freequant/trade/TradeProvider.h>

namespace FreeQuant {

namespace Detail {
    class FixProviderImpl;
}

class FixTradeProvider : public TradeProvider {
public:
    explicit FixTradeProvider(std::string connection, FreeQuant::TradeProvider::Callback *callback = 0);
    virtual ~FixTradeProvider();

    void setCallback(FreeQuant::TradeProvider::Callback *callback);

    void connect();
    void connect(const std::string& connection, bool block = false);
    void disconnect();
    bool isConnected() const;
    std::string name() const { return "FIX"; }

    void logon();
    void logout();

    std::vector<std::string> availableExchanges() const;
    std::vector<std::string> availableInstruments() const;

    void sendOrder(FreeQuant::Order& order);
    void cancelOrder(FreeQuant::Order& order);
    void replaceOrder(FreeQuant::Order& order);

    void subscribe(std::vector<std::string> symbols);
    void unsubscribe(std::vector<std::string> symbols);

    void updateIntrument(std::string symbol, bool block = false);
    void updateIntrument(FreeQuant::Instrument& instrument);

    bool orderTypeSupported(FreeQuant::Order::Type type) { return true; }
private:
    class Impl;
    Impl *_impl;
    std::unique_ptr<FreeQuant::Detail::FixProviderImpl> _impl1;
};


} // namespace FreeQuant

#endif // FQ_TRADE_FIXTRADEPROVIDER_H
