#ifndef FQ_STRATEGY_BASESTRATEGY_H
#define FQ_STRATEGY_BASESTRATEGY_H

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

    BaseStrategy() :
        _runningMode(Simulation), _running(false), _tick(0), _length(0),
        _signal_set(_io_service, SIGINT, SIGTERM) {
    }

    virtual ~BaseStrategy() {}

    void setRunningLength(unsigned long length) {
        _length = length;
    }

    bool running() {
        boost::lock_guard<boost::mutex> lock(_mutex);
        return _running;
    }

    int exec() {
        return 0;
    }

    void init() {
        onInit();
    }

    void destroy() {
        onDestroy();
    }

    void start() {
        _signal_set.async_wait(boost::bind(&BaseStrategy::onBreak, this));
        boost::thread(boost::bind(&boost::asio::io_service::run, &_io_service));

        setRunning(true);
        onStart();

        switch (runningMode()) {
        case Simulation:
            _thread.reset(new boost::thread(boost::bind(&BaseStrategy::runSimulation, this)));
        case Paper:
        case Live:
        default:
            runLiveOrPaper();
        }
    }

    void stop() {
        setRunning(false);
        switch (runningMode()) {
        case Simulation:
            break;
        case Paper:
        case Live:
            onStop();
        default:
            break;
        }
    }

    RunningMode runningMode() const { return _runningMode; }
    void setRunningMode(RunningMode mode) { _runningMode = mode; }

    virtual void onInit() = 0;
    virtual void onDestroy() = 0;
    virtual void onStart() = 0;
    virtual void onStop() = 0;

protected:
    virtual void onStep() = 0;
private:
    unsigned long runningLength() const { return _length; }
    unsigned long runningTick() const { return _tick; }

    void onBreak() {
        if (running()) {
            stop();
        }
    }

    void setRunning(bool value) {
        boost::lock_guard<boost::mutex> lock(_mutex);
        _running = value;
    }

    void runSimulation() {
        while (true) {
            if (!running())
                break;
            if (runningTick() > runningLength()) {
                setRunning(false);
                break;
            }
            onStep();
            ++_tick;
        }
        onStop();
    }

    void runLiveOrPaper() {

    }

    RunningMode _runningMode;
    bool _running;
    unsigned long _tick;
    unsigned long _length;
    boost::asio::io_service _io_service;
    boost::asio::signal_set _signal_set;

    boost::shared_ptr<boost::thread> _thread;
    boost::mutex _mutex;
};

} // namespace FreeQuant

#endif // FQ_STRATEGY_ENGINE_H
