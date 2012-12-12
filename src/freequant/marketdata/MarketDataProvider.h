#ifndef FQ_MARKETDATA_MARKETDATAPROVIDER_H
#define FQ_MARKETDATA_MARKETDATAPROVIDER_H

#include <string>
#include <vector>

#include <freequant/Provider.h>
#include <freequant/marketdata/Bar.h>
#include <freequant/marketdata/Tick.h>

namespace FreeQuant {

class MarketDataProviderCallback {
public:
    virtual ~MarketDataProviderCallback() {}
    virtual void onConnected() = 0;
    virtual void onDisconnected() = 0;
    virtual void onSubscribed() = 0;
    virtual void onUnsubscribed() = 0;
    virtual void onBar(const Bar&) = 0;
    virtual void onTick(const Tick&) = 0;
};

class MarketDataProvider {
public:
    typedef std::vector<std::string> Symbols;

    class Callback {
    public:
        virtual ~Callback() {}
        virtual void onConnected() = 0;
        virtual void onDisconnected() = 0;
        virtual void onSubscribed() = 0;
        virtual void onUnsubscribed() = 0;
        virtual void onBar(const Bar&) = 0;
        virtual void onTick(const Tick&) = 0;
    };

    virtual ~MarketDataProvider() {}
    virtual void setCallback(Callback *callback) = 0;
    virtual void setCallback(MarketDataProviderCallback *callback) = 0;
    virtual void connect(bool block = true) = 0;
    virtual void disconnect(bool block = true) = 0;
    virtual bool isConnected() const = 0;
    virtual std::string name() const = 0;
    virtual void subscribe(const Symbols&) = 0;
    virtual void unsubscribe(const Symbols&) = 0;
    virtual void subscribe(const std::string&) = 0;
    virtual void unsubscribe(const std::string&) = 0;
};

class DefaultMarketDataProviderCallback : public MarketDataProvider::Callback {
public:
    void onConnected() {}
    void onDisconnected() {}
    void onSubscribed() {}
    void onUnsubscribed() {}
    void onBar(const Bar&) {}
    void onTick(const Tick&) {}
};

} // namespace FreeQuant

#endif //FQ_MARKETDATA_MARKETDATAPROVIDER_H
