#include "CtpGateway.h"
#include <freequant/providers/ctp/CtpMarketDataProvider.h>
#include <freequant/providers/ctp/CtpTradeProvider.h>
#include <freequant/utils/Utility.h>
#include <freequant/fix/MessageFactory.h>

#include <quickfix/fix50sp2/NewOrderSingle.h>
#include "ThostFtdcTraderApi.h"
using namespace FIX;

namespace FreeQuant {

struct CtpFfunctionality {
    void updateUserPassword(const std::string& oldPassword, const std::string& newPassword);
    void updateAccountPassword(const std::string& oldPassword, const std::string& newPassword);
    void queryOrderMaxVol();
    void queryOrder();
    void queryTrade();
    void confirmSettlement();
    void queryPosition();
    void queryInstrument();
    void queryExchange();
    void queryBank();
    void queryBrokers();
    void queryTradingCode();
    void queryBrokerTradingParams();
    void queryBrokerTradingAlgos();
    void queryTradingAccount();
    void queryInvestor();
    void queryInstrumentMarginRate();
    void queryDepthMarketData();
    void queryTransferBank();
    void queryNotice();
    void queryTradingNotice();
};

class CtpGateway::TradeCallback {
public:
    TradeCallback(CtpGateway *provider) : provider(provider) {}
    virtual ~TradeCallback() {}
    void onConnected() {}
    void onDisconnected() {}
private:
    CtpGateway *provider;
};

class CtpGateway::MdCallback {
public:
    MdCallback(CtpGateway *provider) : provider(provider) {}
    virtual ~MdCallback() {}
    void onConnected() {}
    void onDisconnected() {}
private:
    CtpGateway *provider;
};

CtpGateway::CtpGateway(const std::string& filename) : api(0) {
    _mdCallback.reset(new MdCallback(this));
    _ctpMdProvider.reset(new CtpMarketDataProvider(""));
    _tradeCallback.reset(new TradeCallback(this));
    _ctpTradeProvider.reset(new CtpTradeProvider(""));

    // CTP connection
    std::string connection = "";
    connect(connection);
}

CtpGateway::~CtpGateway() {
    disconnect();
}

void CtpGateway::connect(const std::string& connection) {
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

void CtpGateway::disconnect() {
    reset();
}

void CtpGateway::reset() {
    if (api) {
        api->RegisterSpi(0);
        api->Release();
        api = 0;
    }
}

void CtpGateway::onMessage(const FIX44::NewOrderSingle& message, const FIX::SessionID& sessionID) {
    Order order;
    MessageFactory::messageFrom(message, order);
    _ctpTradeProvider->sendOrder(order);
}

void CtpGateway::onMessage(const FIX50SP2::NewOrderSingle& message, const FIX::SessionID& sessionID) {

}

}
