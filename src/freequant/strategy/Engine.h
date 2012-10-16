#ifndef FQ_STRATEGY_ENGINE_H
#define FQ_STRATEGY_ENGINE_H

#include <boost/asio/signal_set.hpp>

#include <freequant/marketdata/marketdataprovider.h>
#include <freequant/trade/TradeProvider.h>

namespace FreeQuant {

class Engine {
public:
    Engine();
    virtual ~Engine() {}
    virtual int exec();
    virtual void onStart() = 0;
    virtual void onStop() = 0;
    virtual void onBreak() = 0;
protected:
    virtual void start() {
        onStart();
    }

    virtual void stop() {
        onStop();
    }

private:
    boost::asio::io_service _io_service;
    boost::asio::signal_set _signal_set;
};

} // namespace FreeQuant

#endif // FQ_STRATEGY_ENGINE_H
