#include "CtpGateway.h"
#include <freequant/trade/CtpTradeProvider.h>

using namespace FIX;

namespace FreeQuant {

class CtpGateway::TradeCallback {
public:
    TradeCallback(CtpGateway *provider) : provider(provider) {}
    virtual ~TradeCallback() {}
    void onConnected() {}
    void onDisconnected() {}
private:
    CtpGateway *provider;
};

CtpGateway::CtpGateway(const std::string& filename) {
    _tradeCallback.reset(new TradeCallback(this));
    _ctpTradeProvider.reset(new CtpTradeProvider(""));
//    _ctpTradeProvider.setCallback();
}

CtpGateway::~CtpGateway() {}
void CtpGateway::onMessage(const FIX44::NewOrderSingle&, const FIX::SessionID&) {

}

}
