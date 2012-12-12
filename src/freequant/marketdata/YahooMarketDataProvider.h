#ifndef FQ_MARKETDATA_YAHOOMARKETDATAPROVIDER_H
#define FQ_MARKETDATA_YAHOOMARKETDATAPROVIDER_H

#include <freequant/marketdata/MarketDataProvider.h>
#include <freequant/utils/HttpClient.h>
#include <freequant/utils/Timer.h>

namespace FreeQuant {

class YahooMarketDataProvider : public MarketDataProvider {
public:
    YahooMarketDataProvider();
    ~YahooMarketDataProvider();
    void connect();
    void disconnect();
    bool isConnected() const { return true; }
    std::string name() const { return "Yahoo"; }

    void subscribe(std::vector<std::string> symbols) {}
    void unsubscribe(std::vector<std::string> symbols) {}
    void subscribe(const std::string& symbol) {}
    void unsubscribe(const std::string& symbol) {}

private:
    FreeQuant::Timer *timer;
    void getQuota();
    FreeQuant::HttpClient client;
};

} // namespace FreeQuant

#endif // FQ_MARKETDATA_YAHOOMARKETDATAPROVIDER_H
