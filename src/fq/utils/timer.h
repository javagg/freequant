#ifndef FQ_UTILS_TIMER_H
#define FQ_UTILS_TIMER_H

#include <boost/bind.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/shared_ptr.hpp>

namespace FreeQuant{ namespace Utils {

class Timer {
public:
    Timer(double interval = 1);
    ~Timer();
    void start();
    void stop();

private:
    void timer_func();

    boost::shared_ptr<boost::asio::io_service> io;
    boost::shared_ptr<boost::asio::deadline_timer> timer;
    double interval;
};

}}

#endif // FQ_UTILS_TIMER_H
