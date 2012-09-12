/*
 * strategy.cpp
 *
 *  Created on: 2012-6-25
 *      Author: alex
 */

#include <iostream>

#include <boost/bind.hpp>
#include <boost/thread.hpp>


#include "strategy.h"

using namespace std;

namespace FreeQuant { namespace Strategy {

Strategy::Strategy() : m_signals(m_io_service, SIGINT, SIGTERM) {
    m_signals.async_wait(boost::bind(&Strategy::handleBreak, this));
}

Strategy::~Strategy() {
	// TODO Auto-generated destructor stub
}

void Strategy::run() {
    while (true) {
        boost::this_thread::sleep(boost::posix_time::seconds(1));
    }
}

void Strategy::handleBreak() {
    cout << "ctrl+c detected!" << endl;
    this->stop();
    exit(0);
}

}} // namespace FreeQuant
