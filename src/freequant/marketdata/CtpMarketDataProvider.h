#ifndef FQ_MARKETDATA_CTPMARKETDATAPROVIDER_H
#define FQ_MARKETDATA_CTPMARKETDATAPROVIDER_H

#include <freequant/marketdata/MarketDataProvider.h>

namespace FreeQuant {

class CtpMarketDataProvider : public MarketDataProvider {
public:
    explicit CtpMarketDataProvider(FreeQuant::MarketDataProvider::Callback *callback = 0);
    virtual ~CtpMarketDataProvider();
    void setCallback(FreeQuant::MarketDataProvider::Callback *callback);
    void connect(bool block = true);
    void disconnect(bool block = true);
    bool isConnected() const;
    std::string name() const { return "CTP"; }
    void subscribe(std::vector<std::string> symbols);
    void unsubscribe(std::vector<std::string> symbols);

private:
    class Impl;
    Impl *_impl;
};

} // namespace FreeQuant

#endif // FQ_MARKETDATA_CTPMARKETDATAPROVIDER_H
