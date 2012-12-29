#ifndef FQ_FIX_CTPSSEGATEWAY_H
#define FQ_FIX_CTPSSEGATEWAY_H

#include <quickfix/Application.h>
#include <quickfix/MessageCracker.h>

#include "ThostFtdcTraderApi.h"

namespace FreeQuant {

class CtpSseMarketDataProvider;
class CtpSseTradeProvider;

class CtpSseGateway : public CThostFtdcTraderSpi, FIX::NullApplication, public FIX::MessageCracker {
public:
    CtpSseGateway(const std::string& filename);
    virtual ~CtpSseGateway();
    void onMessage(const FIX44::NewOrderSingle&, const FIX::SessionID&);
    void onMessage(const FIX44::UserRequest&, const FIX::SessionID&);

    void onMessage(const FIX50SP2::NewOrderSingle&, const FIX::SessionID&);

private:
    friend class TradeCallback;
    class TradeCallback;
//    std::unique_ptr<TradeCallback> _tradeCallback;
//    std::unique_ptr<CtpSseTradeProvider> _ctpTradeProvider;

    friend class MdCallback;
    class MdCallback;
//    std::unique_ptr<MdCallback> _mdCallback;
//    std::unique_ptr<CtpSseMarketDataProvider> _ctpMdProvider;

    CThostFtdcTraderApi *api;
    std::string front;
    std::string userId;
    std::string password;
    std::string brokerId;

    void connect(const std::string& connection);
    void disconnect();
    void reset();
};

}

#endif // FQ_FIX_CTPSSEGATEWAY_H
