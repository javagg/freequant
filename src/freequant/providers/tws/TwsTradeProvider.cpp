#include "TwsTradeProvider.h"
#include "TwsProviderImpl.h"

namespace FreeQuant {

TwsTradeProvider::TwsTradeProvider(const std::string& connection, FreeQuant::TradeProvider::Callback *callback) :
   _impl(new FreeQuant::Detail::TwsProviderImpl(connection, callback)) {
}

TwsTradeProvider::~TwsTradeProvider() {}

void TwsTradeProvider::connect(const std::string& connection, bool block) {

}

void TwsTradeProvider::connect() {
    _impl->connect();
}

void TwsTradeProvider::disconnect() {
    _impl->disconnect();
}

bool TwsTradeProvider::isConnected() const {
    return _impl->isConnected();
}

std::vector<std::string> TwsTradeProvider::availableAccounts() const {
    return _impl->availableAccounts();

}

void TwsTradeProvider::sendOrder(const FreeQuant::Order& order) {

}
void TwsTradeProvider::cancelOrder(const FreeQuant::Order& order) {

}
void TwsTradeProvider::replaceOrder(const FreeQuant::Order& order) {
}

void TwsTradeProvider::updateIntrument(const std::string& symbol, bool block) {
    _impl->updateIntrument(symbol, block);
}

void TwsTradeProvider::updateIntrument(FreeQuant::Instrument& instrument) {

}

}
