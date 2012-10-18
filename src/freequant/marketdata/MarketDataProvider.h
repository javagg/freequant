#ifndef FQ_MARKETDATA_MARKETDATAPROVIDER_H
#define FQ_MARKETDATA_MARKETDATAPROVIDER_H

#include <functional>
#include <string>
#include <vector>

#include <boost/signals2.hpp>
#include <freequant/marketdata/Bar.h>

namespace FreeQuant {
    class Strategy;
}

namespace FreeQuant {

class MarketDataProvider {
public:
    void connect(boost::function<void(const FreeQuant::Bar&)> func) {
        _onBar.connect(func);
    }

    virtual ~MarketDataProvider() {}
    virtual void connect(bool block = true) = 0;
    virtual void disconnect(bool block = true) = 0;
    virtual bool isConnected() const = 0;
    virtual std::string name() const = 0;
    virtual void subscribe(std::vector<std::string> symbols) = 0;
    virtual void unsubscribe(std::vector<std::string> symbols) = 0;

    virtual void onConnected() = 0;
    virtual void onDisconnected() = 0;

protected:
    typedef boost::signals2::signal<void (const FreeQuant::Bar&)> OnBar;
    OnBar _onBar;
};

} // namespace FreeQuant

#endif //FQ_MARKETDATA_MARKETDATAPROVIDER_H
