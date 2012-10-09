#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "Timer.h"

namespace FreeQuant{ namespace Utils {

Timer::Timer(const double interval) :
    _interval(interval),
    _io_service(),
    _timer(_io_service, boost::posix_time::seconds(_interval)) {
}

Timer::~Timer() {
    _timer.cancel();
}

void Timer::connect(const Timeout::slot_type &subscriber) {
    timeout.connect(subscriber);
}

void Timer::start() {
    _timer.expires_from_now( boost::posix_time::seconds(_interval));
    _timer.async_wait(boost::bind(&Timer::handler, this, boost::asio::placeholders::error));
    boost::thread thread(boost::bind(&boost::asio::io_service::run, &_io_service));
}

void Timer::handler(const boost::system::error_code& error) {
     if (error != boost::asio::error::operation_aborted) {
        timeout();
        _timer.expires_from_now( boost::posix_time::seconds(_interval));
        _timer.async_wait(boost::bind(&Timer::handler, this, boost::asio::placeholders::error));
     }
}

}}
