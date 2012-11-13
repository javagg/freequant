#ifndef FQ_STRATEGY_BASESTRATEGY_H
#define FQ_STRATEGY_BASESTRATEGY_H

#include <memory>
#include <boost/asio/io_service.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

namespace FreeQuant {

class BaseStrategy  {
public:
    /*!
     * \enum RunningMode
     * An enum type.
     * The documentation block cannot be put after the enum!
     */
    enum RunningMode {
        Simulation,
        Paper,
        Live
    };

    BaseStrategy();
    virtual ~BaseStrategy();
    void setRunningLength(unsigned long length) { _length = length; }
    bool running();
    int exec() { return 0; }
    void init();
    void destroy();
    void start();
    void stop();
    RunningMode runningMode() const { return _runningMode; }
    void setRunningMode(RunningMode mode) { _runningMode = mode; }

    virtual void onInit() = 0;
    virtual void onDestroy() = 0;
    virtual void onStart() = 0;
    virtual void onStop() = 0;
protected:
    virtual void onStep() = 0;
    unsigned long runningLength() const { return _length; }
    unsigned long runningTick() const { return _tick; }
private:
    void onBreak();
    void setRunning(bool value);
    void runSimulation();

    void doStop();
    RunningMode _runningMode;
    bool _running;
    unsigned long _tick;
    unsigned long _length;
    boost::asio::io_service _io_service;
    boost::asio::signal_set _signal_set;
    std::shared_ptr<boost::thread> _io_service_thread;
    std::shared_ptr<boost::thread> _simulation_thread;
    boost::mutex _mutex;
};

} // namespace FreeQuant

#endif // FQ_STRATEGY_ENGINE_H
