#ifndef FQ_MARKETDATA_YAHOOMARKETDATAPROVIDER_H
#define FQ_MARKETDATA_YAHOOMARKETDATAPROVIDER_H

#include <freequant/marketdata/MarketDataProvider.h>
#include <freequant/utils/httpclient.h>
#include <freequant/utils/Timer.h>

namespace FreeQuant {

class YahooMarketDataProvider : public MarketDataProvider {
public:
    YahooMarketDataProvider();
    virtual ~YahooMarketDataProvider();
    virtual void connect();
    virtual void disconnect();
    virtual bool isConnected() const { return true; }
    virtual std::string name() const { return "yahoo"; }

    virtual void subscribe(std::vector<std::string> symbols) {}
    virtual void unsubscribe(std::vector<std::string> symbols) {}
private:
    FreeQuant::Timer *timer;
    void getQuota();
    FreeQuant::HttpClient client;
};

} // namespace FreeQuant

#endif // FQ_MARKETDATA_YAHOOMARKETDATAPROVIDER_H
