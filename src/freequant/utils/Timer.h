#ifndef FQ_UTILS_TIMER_H
#define FQ_UTILS_TIMER_H

#include <boost/bind.hpp>
#include <boost/date_time/time_duration.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <boost/thread.hpp>

namespace FreeQuant {

class Timer {
public:
    Timer(int milliseconds = 1000, boost::function<void()> observer = boost::function<void()>());
    ~Timer();
    void start();
    void stop();

private:
    typedef boost::signals2::signal<void()> Timeout;

    void handler(const boost::system::error_code& error);
    Timeout _timeout;
    boost::posix_time::time_duration _duration;
    boost::asio::io_service _io_service;
    boost::asio::deadline_timer _timer;
    boost::shared_ptr<boost::thread> _thread;
};

} // namespace FreeQuant

#endif // FQ_UTILS_TIMER_H
