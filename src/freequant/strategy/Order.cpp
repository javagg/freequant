#include <freequant/trade/TradeProvider.h>

#include "Order.h"

namespace FreeQuant {

class OrderTradeProvider : public FreeQuant::TradeProvider {
public:
    void connect() {}
    void disconnect() {}
    bool isConnected() { return true; }
    std::string name() { return "OrderTradeProvider"; }

    virtual std::vector<std::string> availableExchanges() const { return std::vector<std::string>(); }
    virtual std::vector<std::string> availableInstruments() const { return std::vector<std::string>(); }

    void sendOrder(FreeQuant::Order& order) {

    }

    void cancelOrder(FreeQuant::Order& order) {

    }

    virtual void replaceOrder(FreeQuant::Order& order) {

    }

    void subscribe(std::vector<std::string> symbols) {

    }

    void unsubscribe(std::vector<std::string> symbols) {

    }

    void updateIntrument(std::string symbol, bool block = false) {}

    void updateIntrument(FreeQuant::Instrument& instrument) {}
};

Order::Order() {
	// TODO Auto-generated constructor stub

}

Order::~Order() {
	// TODO Auto-generated destructor stub
}

void Order::cancel() {

}

void Order::replace() {

}

void Order::send() {
    _tradeProvider->sendOrder(*this);
}

} // namespace FreeQuant
