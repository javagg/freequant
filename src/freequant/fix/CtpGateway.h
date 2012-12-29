#ifndef FQ_FIX_CTPGATEWAY_H
#define FQ_FIX_CTPGATEWAY_H

#include <quickfix/Application.h>
#include <quickfix/MessageCracker.h>

#include "ThostFtdcTraderApi.h"

namespace FreeQuant {

class CtpMarketDataProvider;
class CtpTradeProvider;

class CtpGateway : public CThostFtdcTraderSpi, FIX::NullApplication, public FIX::MessageCracker {
public:
    CtpGateway(const std::string& filename);
    virtual ~CtpGateway();
    void onMessage(const FIX44::NewOrderSingle&, const FIX::SessionID&);
    void onMessage(const FIX50SP2::NewOrderSingle&, const FIX::SessionID&);

private:

    friend class TradeCallback;
    class TradeCallback;
    std::unique_ptr<TradeCallback> _tradeCallback;
    std::unique_ptr<CtpTradeProvider> _ctpTradeProvider;

    friend class MdCallback;
    class MdCallback;
    std::unique_ptr<MdCallback> _mdCallback;
    std::unique_ptr<CtpMarketDataProvider> _ctpMdProvider;

    CThostFtdcTraderApi *api;
    std::string front;
    std::string userId;
    std::string password;
    std::string brokerId;
//    std::string connection;

    void connect(const std::string& connection);
    void disconnect();
    void reset();

//    friend class CtpTradeSpi;
//    class CtpTradeSpi;
//    std::unique_ptr<CtpTradeSpi> *spi;
};

}

#endif // FQ_FIX_CTPGATEWAY_H
