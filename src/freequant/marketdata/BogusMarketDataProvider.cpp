#include <boost/bind.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "BogusMarketDataProvider.h"

namespace FreeQuant {

BogusMarketDataProvider::BogusMarketDataProvider() {
//    io = new boost::asio::io_service();
//    mTimer = new boost::asio::deadline_timer(*io, boost::posix_time::seconds(1));
}

BogusMarketDataProvider::~BogusMarketDataProvider() {
//    delete timer;
//    delete io;
}

void BogusMarketDataProvider::connect() {
//    io = new boost::asio::io_service();
//    timer = new boost::asio::deadline_timer(*io, boost::posix_time::seconds(1));
//    timer->async_wait(boost::bind(&BogusProvoder::timer_func, this));
}

void BogusMarketDataProvider::disconnect() {

}

bool BogusMarketDataProvider::isConnected() {
    return false;
}

void BogusMarketDataProvider::onData() {

}

} // namespace FreeQuant
