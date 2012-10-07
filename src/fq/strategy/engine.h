#ifndef FQ_STRATEGY_ENGINE_H
#define FQ_STRATEGY_ENGINE_H

#include <boost/thread.hpp>

#include <fq/marketdata/marketdataprovider.h>
#include <fq/trade/tradeprovider.h>

namespace FreeQuant { namespace Strategy {

class Engine {
public:
    Engine();
    virtual ~Engine() {}
    void start();
    void stop() {}
    void run();

private:
    bool running;
    boost::thread *m_thread;
};

}}

#endif // FQ_STRATEGY_ENGINE_H
