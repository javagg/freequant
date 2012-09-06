#include <boost/bind.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "bogusprovoder.h"

namespace FreeQuant { namespace MarketData {

BogusProvoder::BogusProvoder() {
//    io = new boost::asio::io_service();
//    mTimer = new boost::asio::deadline_timer(*io, boost::posix_time::seconds(1));
}

BogusProvoder::~BogusProvoder() {
//    delete timer;
//    delete io;
}

void BogusProvoder::connect() {
//    io = new boost::asio::io_service();
//    timer = new boost::asio::deadline_timer(*io, boost::posix_time::seconds(1));
//    timer->async_wait(boost::bind(&BogusProvoder::timer_func, this));
}

void BogusProvoder::disconnect() {

}

bool BogusProvoder::isConnected() {
    return false;
}

void BogusProvoder::onData() {

}

}}
