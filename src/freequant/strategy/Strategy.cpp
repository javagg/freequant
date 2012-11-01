#include <iostream>

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/assign.hpp>

#include <freequant/indicators/Indicator.h>
#include <freequant/trade/CtpTradeProvider.h>

#include "Strategy.h"

using namespace std;

namespace FreeQuant {

class Strategy::MdProviderCallback : public DefaultMarketDataProviderCallback {
public:
    Strategy *_strategy;
    MdProviderCallback(Strategy *strategy) : _strategy(strategy) {}
    void onBar(FreeQuant::Bar& bar) {
        _strategy->onBar(bar);
    }

    void onConnected() {
        _strategy->onMarketDataProviderConnected();
    }
};

class Strategy::TradeProviderCallback : public DefaultTradeProviderCallback {

};


Strategy::Strategy() :
    _mdProvider(0), m_tradeProvider(0),
    _mdCallback(new Strategy::MdProviderCallback(this)),
    _tradeCallback(new Strategy::TradeProviderCallback()) {
}

Strategy::~Strategy() {
    delete _mdCallback; _mdCallback = 0;
    delete _tradeCallback; _tradeCallback = 0;
}

void Strategy::setTradeProvider(FreeQuant::TradeProvider *provider) {
    m_tradeProvider = provider;
}

void Strategy::setMarketDataProvider(FreeQuant::MarketDataProvider *provider) {
    _mdProvider = provider;
    _mdProvider->setCallback(_mdCallback);
}

void Strategy::start() {
    Engine::start();
    _mdProvider->connect(true);
}

void Strategy::stop() {
    _mdProvider->disconnect();
//    m_tradeProvider->disconnect();
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

void Strategy::addSymbols(std::vector<std::string>& symbols) {
    _symbols.insert(symbols.begin(), symbols.end());
}

void Strategy::onMarketDataProviderConnected() {
    std::cout << "onMarketDataProviderConnected" << std::endl;
    _mdProvider->subscribe(vector<string>(_symbols.begin(), _symbols.end()));
}

} // namespace FreeQuant
