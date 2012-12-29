#ifndef CtpSseMarketDataProvider_H
#define CtpSseMarketDataProvider_H

#include <memory>
#include <freequant/marketdata/MarketDataProvider.h>

namespace FreeQuant { namespace Ext {

class CtpSseMarketDataProvider : public FreeQuant::MarketDataProvider {
public:
    explicit CtpSseMarketDataProvider(const std::string& connection, FreeQuant::MarketDataProvider::Callback *callback = 0);
    explicit CtpSseMarketDataProvider(const std::string& connection, MarketDataProviderCallback *callback);
    ~CtpSseMarketDataProvider();
    void setCallback(Callback *callback);
    void setCallback(MarketDataProviderCallback *callback);
    void connect(bool block = true) = 0;
    void disconnect(bool block = true);
    bool isConnected() const = 0;
    std::string name() const = 0;
    void subscribe(const Symbols& symbols);
    void unsubscribe(const Symbols& symbols);
    void subscribe(const std::string& symbol);
    void unsubscribe(const std::string& symbol);
private:
    class Impl;
    std::unique_ptr<Impl> _impl;
};

}} // namespace

#endif // CtpSseMarketDataProvider_H
