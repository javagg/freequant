#ifndef FQ_MARKETDATA_TWSPROVIDER_H
#define FQ_MARKETDATA_TWSPROVIDER_H

#include <fq/marketdata/provider.h>

class EWrapper;

namespace FreeQuant { namespace MarketData {

class TwsProvider : public Provider {
public:
    TwsProvider();
    ~TwsProvider();
    virtual void connect();
    virtual void disconnect();
    virtual bool isConnected() const { return false; }
    virtual std::string name() const { return "TWS"; }

private:
    EWrapper *wrapper;
};

}}

#endif // FQ_MARKETDATA_TWSPROVIDER_H
