#ifndef FQ_UTILS_TIMER_H
#define FQ_UTILS_TIMER_H

#include <boost/asio/io_service.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/signals2.hpp>

namespace FreeQuant{ namespace Utils {

class Timer {
public:
    typedef boost::signals2::signal<void ()> Timeout;

    Timer(const double interval = 1);
    ~Timer();
    void start();
    void connect(const Timeout::slot_type &subscriber);

private:
    void handler(const boost::system::error_code& error);
    Timeout timeout;
    boost::asio::io_service *io;
    boost::asio::deadline_timer *timer;
    double interval;
};

}}

#endif // FQ_UTILS_TIMER_H
