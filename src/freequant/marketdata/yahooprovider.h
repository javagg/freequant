#ifndef FQ_MARKETDATA_YAHOOPROVIDER_H
#define FQ_MARKETDATA_YAHOOPROVIDER_H

#include <freequant/marketdata/marketdataprovider.h>
#include <freequant/utils/httpclient.h>
#include <freequant/utils/Timer.h>

namespace FreeQuant {

class YahooProvider : public MarketDataProvider {
public:
    YahooProvider();
    virtual ~YahooProvider();
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

#endif // FQ_MARKETDATA_YAHOOPROVIDER_H
