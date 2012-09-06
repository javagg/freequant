#include <boost/bind.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "timer.h"

namespace FreeQuant{ namespace Utils {

Timer::Timer(double i) : interval(i) {

}

Timer::~Timer() {
    stop();
}

void Timer::start() {
    io =  boost::shared_ptr<boost::asio::io_service>(new boost::asio::io_service());
    timer = boost::shared_ptr<boost::asio::deadline_timer>(new boost::asio::deadline_timer(*io, boost::posix_time::seconds(interval)));
}

void Timer::stop() {

}

}}
