#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "Timer.h"

namespace FreeQuant {

Timer::Timer(int milliseconds, std::function<void()> observer) :
    _timeout(observer),
    _duration(boost::posix_time::milliseconds(milliseconds)),
    _io_service(),
    _timer(_io_service, _duration) {
    timeout.connect(_timeout);
}

Timer::~Timer() {
    stop();
}

void Timer::start() {
    _timer.expires_from_now(_duration);
    _timer.async_wait(boost::bind(&Timer::handler, this, boost::asio::placeholders::error));
    _thread.reset(new std::thread(boost::bind(&boost::asio::io_service::run, &_io_service)));
}

void Timer::stop() {
    _timer.cancel();
    if (_thread && _thread->joinable()) _thread->join();
}

void Timer::handler(const boost::system::error_code& error) {
    if (error != boost::asio::error::operation_aborted) {
        timeout();
        _timer.expires_from_now(_duration);
        _timer.async_wait(boost::bind(&Timer::handler, this, boost::asio::placeholders::error));
    }
}

}
