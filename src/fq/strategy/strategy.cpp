/*
 * strategy.cpp
 *
 *  Created on: 2012-6-25
 *      Author: alex
 */

#include <iostream>

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/assign.hpp>

#include <fq/marketdata/ctp/ctpmarketdataprovider.h>
#include <fq/trade/ctptradeprovider.h>

#include "strategy.h"

using namespace std;

namespace FreeQuant { namespace Strategy {

//Strategy::Strategy() : m_signals(m_io_service, SIGINT, SIGTERM) {
//    m_signals.async_wait(boost::bind(&Strategy::handleBreak, this));
//}

Strategy::Strategy() : m_mdProvider(0), m_tradeProvider(0) {

}

Strategy::~Strategy() {

}

void Strategy::setTradeProvider(FreeQuant::Trade::TradeProvider *provider) {
    m_tradeProvider = provider;
}

void Strategy::setMarketDataProvider(FreeQuant::MarketData::MarketDataProvider *provider) {
    m_mdProvider = provider;
}

int Strategy::exec() {
    onInit();
    m_mdProvider->connect();

    vector<string> symbols = boost::assign::list_of("IF1210")("MSFT");

    m_mdProvider->subscribe(symbols);
    while (true) {
        boost::this_thread::sleep(boost::posix_time::seconds(1));
    }
    return 0;
}

void Strategy::handleBreak() {
    cout << "ctrl+c detected!" << endl;
    this->stop();
    exit(0);
}

}} // namespace FreeQuant
