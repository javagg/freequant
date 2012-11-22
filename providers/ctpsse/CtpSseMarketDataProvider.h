#ifndef CtpSseMarketDataProvider_H
#define CtpSseMarketDataProvider_H

#include <memory>
#include <freequant/marketdata/MarketDataProvider.h>

namespace FreeQuant { namespace Ext {

class CtpSseMarketDataProvider : public FreeQuant::MarketDataProvider {
public:
    explicit CtpSseMarketDataProvider(const std::string& connection, FreeQuant::MarketDataProvider::Callback *callback = 0);
    ~CtpSseMarketDataProvider();
    void setCallback(Callback *callback);
    void connect(bool block = true) = 0;
    void disconnect(bool block = true);
    bool isConnected() const = 0;
    const std::string& name() const = 0;
    void subscribe(const Symbols& symbols);
    void unsubscribe(const Symbols& symbols);
private:
    class Impl;
    std::unique_ptr<Impl> _impl;
};

}} // namespace

#endif // CtpSseMarketDataProvider_H
