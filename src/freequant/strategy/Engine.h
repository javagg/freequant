#ifndef FQ_STRATEGY_ENGINE_H
#define FQ_STRATEGY_ENGINE_H

#include <boost/asio/signal_set.hpp>

#include <freequant/marketdata/MarketDataProvider.h>
#include <freequant/trade/TradeProvider.h>

namespace FreeQuant {

class Engine {
public:
    Engine();
    virtual ~Engine() {}
    virtual int exec();
    virtual bool running() const { return false; }
    virtual void start() {
        onStart();
    }

    virtual void stop() {
        onStop();
    }
    virtual void onStart() = 0;
    virtual void onStop() = 0;
    virtual void onBreak() = 0;
private:
    boost::asio::io_service _io_service;
    boost::asio::signal_set _signal_set;
};

} // namespace FreeQuant

#endif // FQ_STRATEGY_ENGINE_H
