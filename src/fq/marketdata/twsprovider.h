#ifndef FQ_MARKETDATA_TWSPROVIDER_H
#define FQ_MARKETDATA_TWSPROVIDER_H

#include <fq/marketdata/marketdataprovider.h>

namespace FreeQuant { namespace MarketData {

class TwsEWrapper;

class TwsProvider : public MarketDataProvider {
public:
    TwsProvider();
    virtual ~TwsProvider();
    virtual void connect();
    virtual void disconnect();
    virtual bool isConnected() const;
    virtual std::string name() const { return "TWS"; }
    virtual void subscribe(std::vector<std::string> symbols);
    virtual void unsubscribe(std::vector<std::string> symbols);

private:
    TwsEWrapper *wrapper;
};

}}

#endif // FQ_MARKETDATA_TWSPROVIDER_H
