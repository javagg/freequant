#ifndef FQ_MARKETDATA_CTPMARKETDATAPROVIDER_H
#define FQ_MARKETDATA_CTPMARKETDATAPROVIDER_H

#include <memory>

#include <freequant/marketdata/MarketDataProvider.h>

namespace FreeQuant {

class CtpMarketDataProvider : public MarketDataProvider {
    typedef MarketDataProvider Base;
//    typedef MarketDataProvider::Callback Callback;
public:
    explicit CtpMarketDataProvider(const std::string& connection, FreeQuant::MarketDataProvider::Callback *callback = 0);
    virtual ~CtpMarketDataProvider();
    void setCallback(FreeQuant::MarketDataProvider::Callback *callback);
    void connect(bool block = true);
    void disconnect(bool block = true);
    bool isConnected() const;
    std::string name() const { return "CTP"; }
    void subscribe(const Symbols& symbols);
    void unsubscribe(const Symbols& symbols);

private:
    class Impl;
    std::unique_ptr<Impl> _impl;
};

} // namespace FreeQuant

#endif // FQ_MARKETDATA_CTPMARKETDATAPROVIDER_H
