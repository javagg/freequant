#ifndef FQ_UTILS_TIMER_H
#define FQ_UTILS_TIMER_H

#include <boost/asio/io_service.hpp>
#include <boost/asio/deadline_timer.hpp>

namespace FreeQuant{ namespace Utils {

class Timer {
public:
    Timer(const double interval = 1);
    ~Timer();
    void start();

private:
    void handler(const boost::system::error_code& error);

    boost::asio::io_service *io;
    boost::asio::deadline_timer *timer;
    double interval;
};

}}

#endif // FQ_UTILS_TIMER_H
