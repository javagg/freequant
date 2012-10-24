#include <iostream>

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/assign.hpp>

#include <freequant/indicators/indicator.h>
#include <freequant/trade/CtpTradeProvider.h>

#include "strategy.h"

using namespace std;

namespace FreeQuant {

Strategy::Strategy() : m_mdProvider(0), m_tradeProvider(0) {

}

Strategy::~Strategy() {

}

void Strategy::setTradeProvider(FreeQuant::TradeProvider *provider) {
    m_tradeProvider = provider;
}

void Strategy::setMarketDataProvider(FreeQuant::MarketDataProvider *provider) {
    m_mdProvider = provider;
    m_mdProvider->connect(boost::bind(&Strategy::onBar, this, _1));
    m_mdProvider->connect(boost::bind(&Strategy::handleBar, this, _1));
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

void Strategy::handleBar(const FreeQuant::Bar& bar) {
    std::for_each(
        m_indictors.begin(),
        m_indictors.end(),
        boost::bind(&Indicator::onBar, _1, bar)
    );
}

void Strategy::addIndicator(Indicator *indicator) {
    m_indictors.push_back(indicator);
}

} // namespace FreeQuant
