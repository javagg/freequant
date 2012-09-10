#ifndef FQ_TRADE_CTPTRADEPROVIDER_H
#define FQ_TRADE_CTPTRADEPROVIDER_H

#include <fq/trade/tradeprovider.h>

namespace FreeQuant { namespace Trade {

class TraderSpi;

class CtpTradeProvider : public TradeProvider {
public:
    CtpTradeProvider();
    virtual ~CtpTradeProvider();
    virtual void connect();
    virtual void disconnect();
    virtual bool isConnected() const;
    virtual std::string name() const { return "CTP"; }

private:
    TraderSpi *spi;
};

}}

#endif // FQ_TRADE_CTPTRADEPROVIDER_H
