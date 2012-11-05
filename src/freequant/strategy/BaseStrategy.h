#ifndef FQ_STRATEGY_BASESTRATEGY_H
#define FQ_STRATEGY_BASESTRATEGY_H

#include <boost/asio/signal_set.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

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

    bool running() const {
        boost::unique_lock<boost::mutex> lock(_mutex);
        return _running;
    }

    void start() {
        _signal_set.async_wait(boost::bind(&BaseStrategy::onBreak, this));
        boost::thread(boost::bind(&boost::asio::io_service::run, _io_service));
        switch (runningMode()) {
        case Simulation:
            _thread.reset(new boost::thread(boost::bind(&BaseStrategy::runSimulation, this)));
            break;
        case Paper:
        case Live:
        default:
            runLiveOrPaper();
        }
    }

    void stop() {
        switch (runningMode()) {
        case Simulation:
            setRunning(false);
            break;
        case Paper:
        case Live:
        default:
            break;
        }
    }

    RunningMode runningMode() const { return _runningMode; }
    void setRunningMode(RunningMode mode) { _runningMode = mode; }

    unsigned long runningLength() const { return _length; }
    unsigned long runningTick() const { return _tick; }

    virtual void onStart();
    virtual void onStop();
private:
    void onBreak() {
        if (running()) {
            stop();
        }
    }

    void setRunning(bool value) {
        boost::unique_lock<boost::mutex> lock(_mutex);
        _running = value;
    }

    void runSimulation() {
        setRunning(true);
        onStart();
        while (true) {
            if (!running())
                break;
            if (runningTick() > runningLength()) {
                setRunning(false);
                break;
            }
            doStep();
            ++_tick;
        }
        onStop();
    }

    void doStep() {
        boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
        std::cout << "doing work..." << std::endl;
    }

    void runLiveOrPaper();

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
