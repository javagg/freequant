#ifndef FQ_UTILS_TIMER_H
#define FQ_UTILS_TIMER_H

#include <functional>
#include <memory>
#include <mutex>
#include <thread>

#include <boost/asio/io_service.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/signals2.hpp>

namespace FreeQuant{ namespace Utils {

class Timer {
public:
    typedef boost::signals2::signal<void()> Timeout;
    typedef Timeout::slot_type TimeoutFunction;
    Timer(int milliseconds = 1000, std::function<void()> observer = std::function<void()>());
    ~Timer();
    void start();
    void stop();
    void connect(const TimeoutFunction& func) {
        timeout.connect(func);
    }

private:
    void handler(const boost::system::error_code& error);
    std::function<void()> _timeout;
    Timeout timeout;
    boost::posix_time::time_duration _duration;
    boost::asio::io_service _io_service;
    boost::asio::deadline_timer _timer;
    std::shared_ptr<std::thread> _thread;
};

}}

#endif // FQ_UTILS_TIMER_H
