#include "BaseStrategy.h"

namespace FreeQuant {

BaseStrategy::BaseStrategy() :
    _runningMode(Simulation), _running(false), _tick(0), _length(0),
    _signal_set(_io_service, SIGINT, SIGTERM) {
}

BaseStrategy::~BaseStrategy() {}

bool BaseStrategy::running() {
    boost::lock_guard<boost::mutex> lock(_mutex);
    return _running;
}

void BaseStrategy::init() {
    onInit();
}

void BaseStrategy::destroy() {
    onDestroy();
}

void BaseStrategy::start() {
    _io_service.reset();
    _signal_set.async_wait(boost::bind(&BaseStrategy::onBreak, this));
    _io_service_thread.reset(new boost::thread(boost::bind(&boost::asio::io_service::run, &_io_service)));

    setRunning(true);
    onStart();

    switch (runningMode()) {
    case Simulation:
        _simulation_thread.reset(new boost::thread(boost::bind(&BaseStrategy::runSimulation, this)));
    case Paper:
    case Live:
    default:
        break;
    }
}

void BaseStrategy::stop() {
    setRunning(false);
    switch (runningMode()) {
    case Simulation: {
        if (_simulation_thread &&_simulation_thread->joinable())
            _simulation_thread->join();
        break;
    }
    case Paper:
    case Live:
    default:
        break;
    }
    doStop();
}

void BaseStrategy::doStop() {
    std::cout << "called doStop" << std::endl;
//    if (_simulation_thread) {
//        if (_simulation_thread->get_id() != boost::this_thread::get_id()) {
//            if (_simulation_thread->joinable())
//                _simulation_thread->join();
//        }
//    }
    if (!_io_service.stopped()) _io_service.stop();
    if (_io_service_thread && _io_service_thread->joinable())
        _io_service_thread->join();
    onStop();
}

void BaseStrategy::onBreak() {
    if (running()) {
        stop();
    }
}

void BaseStrategy::setRunning(bool value) {
    boost::lock_guard<boost::mutex> lock(_mutex);
    _running = value;
}

void BaseStrategy::runSimulation() {
    while (true) {
        if (!running()) {
         std::cout << "break finish.." << std::endl;
         doStop();
         break;
        }
        if (runningTick() >= runningLength()) {
            setRunning(false);
            std::cout << "normal finish.." << std::endl;
            doStop();
            break;
        }
        onStep();
        ++_tick;
    }

}

} // namespace FreeQuant
