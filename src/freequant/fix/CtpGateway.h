#ifndef FQ_FIX_CTPGATEWAY_H
#define FQ_FIX_CTPGATEWAY_H

#include <quickfix/Application.h>
#include <quickfix/MessageCracker.h>

namespace FreeQuant {

class CtpTradeProvider;

class CtpGateway : public FIX::NullApplication, public FIX::MessageCracker {
public:
    CtpGateway(const std::string& filename);
    virtual ~CtpGateway();
    void onMessage(const FIX44::NewOrderSingle&, const FIX::SessionID&);
private:
    friend class TradeCallback;
    class TradeCallback;
    std::unique_ptr<TradeCallback> _tradeCallback;
    std::unique_ptr<CtpTradeProvider> _ctpTradeProvider;
};

}

#endif // FQ_FIX_CTPGATEWAY_H
