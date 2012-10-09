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

#include <fq/indicators/indicator.h>
#include <fq/marketdata/ctp/ctpmarketdataprovider.h>
#include <fq/trade/ctptradeprovider.h>

#include "strategy.h"

using namespace std;
using namespace FreeQuant::Indicators;

namespace FreeQuant { namespace Strategy {

Strategy::Strategy() : m_mdProvider(0), m_tradeProvider(0) {

}

Strategy::~Strategy() {

}

void Strategy::setTradeProvider(FreeQuant::Trade::TradeProvider *provider) {
    m_tradeProvider = provider;
}

void Strategy::setMarketDataProvider(FreeQuant::MarketData::MarketDataProvider *provider) {
    m_mdProvider = provider;
    m_mdProvider->sub(boost::bind(&Strategy::onBar, this, _1));
    m_mdProvider->sub(boost::bind(&Strategy::handleBar, this, _1));
}

void Strategy::start() {
    Engine::start();
    m_mdProvider->connect();
    vector<string> symbols = boost::assign::list_of("IF1210")("MSFT");
    m_mdProvider->subscribe(symbols);
}

void Strategy::stop() {
    m_mdProvider->disconnect();
    m_tradeProvider->disconnect();
    Engine::stop();
}

void Strategy::handleBar(const FreeQuant::MarketData::Bar& bar) {
    std::for_each(
        m_indictors.begin(),
        m_indictors.end(),
        boost::bind(&Indicator::onBar, _1, bar)
    );
}

void Strategy::addIndicator(Indicator *indicator) {
    m_indictors.push_back(indicator);
}

}} // namespace FreeQuant
