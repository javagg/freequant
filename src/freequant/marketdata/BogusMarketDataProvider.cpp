
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

void BogusMarketDataProvider::setCallback(MarketDataProvider::Callback *callback) {
    _callback = callback;
}

void BogusMarketDataProvider::setCallback(MarketDataProviderCallback *callback) {

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

void BogusMarketDataProvider::subscribe(const Symbols& symbols) {
    _mdGenerator->addSymbols(symbols);
}

void BogusMarketDataProvider::unsubscribe(const Symbols& symbols) {
    _mdGenerator->removeSymbols(symbols);
}

void BogusMarketDataProvider::subscribe(const std::string& symbol) {

}

void BogusMarketDataProvider::unsubscribe(const std::string& symbol) {

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
