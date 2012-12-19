#include <cstring>
#include <iostream>
#include <vector>

#include <boost/format.hpp>

#include <freequant/marketdata/Tick.h>
#include <freequant/utils/Utility.h>
#include <freequant/detail/Atomic.hpp>
#include <freequant/detail/Notifier.h>

#include "CtpMarketDataProvider1.h"

using namespace std;

namespace FreeQuant {

static int requestId = 0;

using Detail::Atomic;
using Detail::Notifier;

class CtpMarketDataProvider1::Impl {

};

CtpMarketDataProvider1::CtpMarketDataProvider1(const std::string& connection, MarketDataProviderCallback *callback)
{
}

CtpMarketDataProvider1::~CtpMarketDataProvider1() {}

void CtpMarketDataProvider1::setCallback(FreeQuant::MarketDataProvider::Callback *callback) {
//    _impl->setCallback(callback);
}

void CtpMarketDataProvider1::setCallback(MarketDataProviderCallback *callback) {
//    _impl->setCallback(callback);
}

void CtpMarketDataProvider1::connect(bool block) {
//    _impl->connect(block);
}

void CtpMarketDataProvider1::disconnect(bool block) {
//    _impl->disconnect(block);
}

bool CtpMarketDataProvider1::isConnected() const {
    return true;
}

void CtpMarketDataProvider1::subscribe(const Symbols& symbols) {
//    _impl->subscribe(symbols);
}

void CtpMarketDataProvider1::unsubscribe(const Symbols& symbols) {
//    _impl->unsubscribe(symbols);
}

void CtpMarketDataProvider1::subscribe(const std::string& symbol) {

}

void CtpMarketDataProvider1::unsubscribe(const std::string& symbol) {

}

} // namespace FreeQuant

