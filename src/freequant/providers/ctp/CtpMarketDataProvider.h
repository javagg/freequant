#ifndef FQ_MARKETDATA_CTPMARKETDATAPROVIDER_H
#define FQ_MARKETDATA_CTPMARKETDATAPROVIDER_H

#include <memory>

#include <freequant/marketdata/MarketDataProvider.h>

namespace FreeQuant {

class CtpMarketDataProvider : public MarketDataProvider {
    typedef MarketDataProvider Base;

public:
    typedef Base::Symbols Symbols;
    explicit CtpMarketDataProvider(const std::string& connection, MarketDataProvider::Callback *callback = 0);
    explicit CtpMarketDataProvider(const std::string& connection, MarketDataProviderCallback *callback);

    virtual ~CtpMarketDataProvider();
    void setCallback(FreeQuant::MarketDataProvider::Callback *callback);
    void setCallback(MarketDataProviderCallback *callback);
    void connect(bool block = true);
    void disconnect(bool block = true);
    bool isConnected() const;
    std::string name() const { return "CTP"; }
    void subscribe(const std::vector<std::string>& symbols);
    void unsubscribe(const Symbols& symbols);
    void subscribe(const std::string& symbol);
    void unsubscribe(const std::string& symbol);

private:
    class Impl;
    std::unique_ptr<Impl> _impl;
};

} // namespace FreeQuant

#endif // FQ_MARKETDATA_CTPMARKETDATAPROVIDER_H
