#ifndef FQ_STRATEGY_ENGINE_H
#define FQ_STRATEGY_ENGINE_H

#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/signal_set.hpp>

#include <fq/marketdata/marketdataprovider.h>
#include <fq/trade/tradeprovider.h>

namespace FreeQuant { namespace Strategy {

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
    boost::asio::deadline_timer _timer;
};

}}

#endif // FQ_STRATEGY_ENGINE_H
