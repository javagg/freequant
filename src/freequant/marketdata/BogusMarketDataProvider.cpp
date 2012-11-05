
#include <boost/bind.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <freequant/utils/RandomMarketDataGenerator.h>

#include "BogusMarketDataProvider.h"

namespace FreeQuant {

BogusMarketDataProvider::BogusMarketDataProvider(Strategy *strategy) :
    _strategy(strategy), _callback(0), _connected(false),
    _mdGenerator(new RandomMarketDataGenerator()){
}

void BogusMarketDataProvider::connect(bool block) {
    _connected = true;
    if (_callback) {
        _callback->onConnected();
    }
}

void BogusMarketDataProvider::disconnect(bool block) {
    _connected = false;
    if (_callback) {
        _callback->onDisconnected();
    }
}

void BogusMarketDataProvider::subscribe(std::vector<std::string> symbols) {
    _mdGenerator->addSymbols(symbols);
}

void BogusMarketDataProvider::unsubscribe(std::vector<std::string> symbols) {
    _mdGenerator->removeSymbols(symbols);
}

void BogusMarketDataProvider::generateBars() {
    MarketDataGenerator::Bars bars = _mdGenerator->generate();
    for(auto i = bars.begin(); i != bars.end(); i++) {
        if (_callback) {
            _callback->onBar(*i);
        }
    }
}

} // namespace FreeQuant
