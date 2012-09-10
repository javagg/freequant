#ifndef FQ_TRADE_CTPPROVIDER_H
#define FQ_TRADE_CTPPROVIDER_H

#include <fq/trade/provider.h>

namespace FreeQuant { namespace Trade {

class TraderSpi;

class CtpProvider : public Provider {
public:
    explicit CtpProvider();
    virtual ~CtpProvider();
    virtual void connect();
    virtual void disconnect();
    virtual bool isConnected() const;
    virtual std::string name() const { return "CTP"; }
private:
    TraderSpi *spi;
};

}}

#endif // FQ_TRADE_CTPPROVIDER_H
