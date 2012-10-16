#ifndef FQ_UTILS_TIMER_H
#define FQ_UTILS_TIMER_H

#include <functional>
#include <memory>
#include <mutex>
#include <thread>

#include <boost/asio/io_service.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/signals2.hpp>
#include <boost/thread.hpp>

namespace FreeQuant{ namespace Utils {

class Timer {
public:
    Timer(int milliseconds = 1000, std::function<void()> observer = std::function<void()>());
    ~Timer();
    void start();
    void stop();

private:
    void handler(const boost::system::error_code& error);
    std::function<void()> _timeout;
    boost::posix_time::time_duration _duration;
    boost::asio::io_service _io_service;
    boost::asio::deadline_timer _timer;
    std::shared_ptr<std::thread> _thread;
};

}}

#endif // FQ_UTILS_TIMER_H
