#include "CtpSseGateway.h"
#include <freequant/providers/ctpsse/CtpSseMarketDataProvider.h>
#include <freequant/providers/ctpsse/CtpSseTradeProvider.h>
#include <freequant/utils/Utility.h>
#include <freequant/fix/MessageFactory.h>

#include <quickfix/fix50sp2/NewOrderSingle.h>

using namespace FIX;

namespace FreeQuant {

class CtpSseGateway::TradeCallback {
public:
    TradeCallback(CtpSseGateway *provider) : provider(provider) {}
    virtual ~TradeCallback() {}
    void onConnected() {}
    void onDisconnected() {}
private:
    CtpSseGateway *provider;
};

class CtpSseGateway::MdCallback {
public:
    MdCallback(CtpSseGateway *provider) : provider(provider) {}
    virtual ~MdCallback() {}
    void onConnected() {}
    void onDisconnected() {}
private:
    CtpSseGateway *provider;
};

CtpSseGateway::CtpSseGateway(const std::string& filename) : api(0) {
//    _mdCallback.reset(new MdCallback(this));
//    _ctpMdProvider.reset(new CtpSseMarketDataProvider("", _mdCallback.get()));
//    _tradeCallback.reset(new TradeCallback(this));
//    _ctpTradeProvider.reset(new CtpSseTradeProvider(""));

    // CTP connection
    std::string connection = "";
    connect(connection);
}

CtpSseGateway::~CtpSseGateway() {
    disconnect();
}

void CtpSseGateway::connect(const std::string& connection) {
    reset();
    auto params = FreeQuant::parseParamsFromString(connection);
    front = params["protocal"] + "://" + params["host"] + ":"  + params["port"]; //"tcp://asp-sim2-front1.financial-trading-platform.com:26213";
    userId = params["userid"];
    password = params["password"];
    brokerId = params["brokerid"];
    api = CThostFtdcTraderApi::CreateFtdcTraderApi("Trade");
    api->RegisterSpi(this);
    api->RegisterFront(const_cast<char*>(front.c_str()));
    api->SubscribePrivateTopic(THOST_TERT_QUICK);
    api->SubscribePrivateTopic(THOST_TERT_QUICK);
    api->Init();
}

void CtpSseGateway::disconnect() {
    reset();
}

void CtpSseGateway::reset() {
    if (api) {
        api->RegisterSpi(0);
        api->Release();
        api = 0;
    }
}

void CtpSseGateway::onMessage(const FIX44::NewOrderSingle& message, const FIX::SessionID& sessionID) {
    Order order;
    MessageFactory::messageFrom(message, order);
//    _ctpTradeProvider->sendOrder(order);
}

void CtpSseGateway::onMessage(const FIX50SP2::NewOrderSingle& message, const FIX::SessionID& sessionID) {

}

void CtpSseGateway::onMessage(const FIX44::UserRequest& message, const FIX::SessionID& sessionID) {

}

}
