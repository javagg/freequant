#ifndef FQ_MARKETDATA_FIXMARKETDATAPROVIDER_H
#define FQ_MARKETDATA_FIXMARKETDATAPROVIDER_H

#include <memory>
#include <freequant/marketdata/MarketDataProvider.h>

namespace FreeQuant {

class FixMarketDataProvider : public MarketDataProvider {
public:
    explicit FixMarketDataProvider(std::string connection, FreeQuant::MarketDataProvider::Callback *callback = 0);
    virtual ~FixMarketDataProvider();
    void setCallback(FreeQuant::MarketDataProvider::Callback *callback);
    void connect(bool block = true);
    void disconnect(bool block = true);
    bool isConnected() const;
    std::string name() const { return "FIX"; }
    void subscribe(const Symbols& symbols);
    void unsubscribe(const Symbols& symbols);

private:
    class Impl;
    std::unique_ptr<Impl> _impl;
};

} // namespace FreeQuant

#endif // FQ_MARKETDATA_FIXMARKETDATAPROVIDER_H
