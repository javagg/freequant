#ifndef FQ_MARKETDATA_TWSPROVIDER_H
#define FQ_MARKETDATA_TWSPROVIDER_H

#include <fq/marketdata/provider.h>

namespace FreeQuant { namespace MarketData {

class TwsEWrapper;

class TwsProvider : public Provider {
public:
    TwsProvider();
    virtual ~TwsProvider();
    virtual void connect();
    virtual void disconnect();
    virtual bool isConnected() const;
    virtual std::string name() const { return "TWS"; }

private:
    TwsEWrapper *wrapper;
};

}}

#endif // FQ_MARKETDATA_TWSPROVIDER_H
