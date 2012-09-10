#ifndef FQ_MARKETDATA_CTP_CTPPROVIDER_H
#define FQ_MARKETDATA_CTP_CTPPROVIDER_H

#include <fq/marketdata/provider.h>
#include "api/trade/win/public/ThostFtdcMdApi.h"

namespace FreeQuant { namespace MarketData {

class MdSpi;

class CtpProvider : public Provider {
public:
    explicit CtpProvider();
    virtual ~CtpProvider();
    virtual void connect();
    virtual void disconnect();
    virtual bool isConnected() const;
    virtual std::string name() const { return "CTP"; }

private:
    MdSpi *spi;
};

}}
#endif // FQ_MARKETDATA_CTP_CTPPROVIDER_H
