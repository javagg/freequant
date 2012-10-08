#ifndef FQ_MARKETDATA_MARKETDATAPROVIDER_H
#define FQ_MARKETDATA_MARKETDATAPROVIDER_H

#include <string>
#include <vector>

#include <boost/signals2.hpp>
#include <fq/marketdata/bar.h>

namespace FreeQuant { namespace Strategy {
    class Strategy;
}}

namespace FreeQuant { namespace MarketData {

class MarketDataProvider {
public:
    typedef boost::signals2::signal<void (const FreeQuant::MarketData::Bar&)> BarSignal;
    typedef BarSignal::slot_type BarSlot;

public:
    void sub(const BarSlot& subscriber) {
        barSignal.connect(subscriber);
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
    BarSignal barSignal;
};

}}

#endif //FQ_MARKETDATA_MARKETDATAPROVIDER_H
