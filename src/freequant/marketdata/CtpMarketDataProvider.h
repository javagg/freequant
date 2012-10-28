#ifndef FQ_MARKETDATA_CTPMARKETDATAPROVIDER_H
#define FQ_MARKETDATA_CTPMARKETDATAPROVIDER_H

#include <freequant/marketdata/MarketDataProvider.h>

namespace FreeQuant {

class CtpMarketDataProvider : public MarketDataProvider {
public:
    explicit CtpMarketDataProvider(FreeQuant::MarketDataProvider::Callback *callback = 0);
    virtual ~CtpMarketDataProvider();
    virtual void connect(bool block = true);
    virtual void disconnect(bool block = true);
    virtual bool isConnected() const;
    virtual std::string name() const { return "CTP"; }
    virtual void subscribe(std::vector<std::string> symbols);
    virtual void unsubscribe(std::vector<std::string> symbols);

    class Impl;
private:
    Impl *_impl;
};

} // namespace FreeQuant

#endif // FQ_MARKETDATA_CTPMARKETDATAPROVIDER_H
