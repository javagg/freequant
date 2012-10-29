#ifndef FQ_MARKETDATA_MARKETDATAPROVIDER_H
#define FQ_MARKETDATA_MARKETDATAPROVIDER_H

#include <functional>
#include <string>
#include <vector>

#include <boost/signals2.hpp>
#include <freequant/Provider.h>
#include <freequant/marketdata/Bar.h>

namespace FreeQuant {
    class Strategy;
}

namespace FreeQuant {

class MarketDataProvider {
public:
    class Callback {
    public:
        virtual ~Callback() {}
        virtual void onConnected() {}
        virtual void onDisconnected() {}
        virtual void onSubscribed() {}
        virtual void onUnsubscribed() {}
        virtual void onBar(FreeQuant::Bar& bar) {}
    };

//    explicit MarketDataProvider(Callback *callback = 0) : _callback(callback) {}
    virtual ~MarketDataProvider() {}

//    void connect(boost::function<void(const FreeQuant::Bar&)> func) {
//        _onBar.connect(func);
//    }

    virtual void setCallback(Callback *callback) = 0;
    virtual void connect(bool block = true) = 0;
    virtual void disconnect(bool block = true) = 0;
    virtual bool isConnected() const = 0;
    virtual std::string name() const = 0;
    virtual void subscribe(std::vector<std::string> symbols) = 0;
    virtual void unsubscribe(std::vector<std::string> symbols) = 0;

//protected:
//    Callback *callback() { return _callback; }
//    typedef boost::signals2::signal<void (const FreeQuant::Bar&)> OnBar;
//    OnBar _onBar;
//private:
//    Callback *_callback;
};

class DefaultMarketDataProviderCallback : public MarketDataProvider::Callback {
public:
    void onConnected() {}
    void onDisconnected() {}
    void onSubscribed() {}
    void onUnsubscribed() {}
    void onBar(FreeQuant::Bar& bar) {}
};

} // namespace FreeQuant

#endif //FQ_MARKETDATA_MARKETDATAPROVIDER_H
