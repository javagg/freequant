#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "timer.h"

namespace FreeQuant{ namespace Utils {

Timer::Timer(const double i) : interval(i) {
    io =  new boost::asio::io_service();
    timer = new boost::asio::deadline_timer(*io, boost::posix_time::seconds(interval));
}

Timer::~Timer() {
    timer->cancel();
    delete timer;
    delete io;
}

void Timer::start() {
    timer->expires_from_now( boost::posix_time::seconds(interval));
    timer->async_wait(boost::bind(&Timer::handler, this, boost::asio::placeholders::error));
    boost::thread t(boost::bind(&boost::asio::io_service::run, io));
}

void Timer::handler(const boost::system::error_code& error) {
    std::cout << "handler!" << std::endl;
//    if (error == boost::asio::error::operation_aborted) {
//        std::cout << "Timer was canceled" << std::endl;
//        return;
//    } else if (error) {
//        std::cout << "Timer error: " << error.message() << std::endl;
//        return;
//    }

    timer->expires_from_now( boost::posix_time::seconds(interval));
    timer->async_wait(boost::bind(&Timer::handler, this, boost::asio::placeholders::error));
}

}}
