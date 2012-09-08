#ifndef FQ_MARKETDATA_YAHOOPROVIDER_H
#define FQ_MARKETDATA_YAHOOPROVIDER_H

#include <fq/utils/httpclient.h>
#include <fq/utils/timer.h>
#include <fq/marketdata/provider.h>

namespace FreeQuant { namespace MarketData {

class YahooProvider : public Provider {
public:
    YahooProvider();
    virtual void connect();
    virtual void disconnect();
    virtual bool isConnected() const { return true; }
    virtual std::string name() const { return "yahoo"; }
private:
    FreeQuant::Utils::Timer *timer;
    void getQuota();

    FreeQuant::Utils::HttpClient client;
};

}}

#endif // FQ_MARKETDATA_YAHOOPROVIDER_H
