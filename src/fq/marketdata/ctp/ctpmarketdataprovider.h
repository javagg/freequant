#ifndef FQ_MARKETDATA_CTP_CTPPROVIDER_H
#define FQ_MARKETDATA_CTP_CTPPROVIDER_H

#include <fq/marketdata/marketdataprovider.h>
#include "api/trade/win/public/ThostFtdcMdApi.h"

namespace FreeQuant { namespace MarketData {

class MdSpi;

class CtpMarketDataProvider : public MarketDataProvider {
public:
    explicit CtpMarketDataProvider();
    virtual ~CtpMarketDataProvider();
    virtual void connect();
    virtual void disconnect();
    virtual bool isConnected() const;
    virtual std::string name() const { return "CTP"; }
    virtual void subscribe(std::vector<std::string> symbols);
    virtual void unsubscribe(std::vector<std::string> symbols);

    void onConnected();
    void onDisconnected();
private:
    MdSpi *spi;
};

}}

#endif // FQ_MARKETDATA_CTP_CTPPROVIDER_H
