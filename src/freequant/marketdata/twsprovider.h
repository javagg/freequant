#ifndef FQ_MARKETDATA_TWSPROVIDER_H
#define FQ_MARKETDATA_TWSPROVIDER_H

#include <string>

#include <freequant/marketdata/MarketDataProvider.h>
#include <freequant/utils/DateTime.h>

namespace FreeQuant {

class TwsEWrapper;

class TwsProvider : public MarketDataProvider {
public:
    TwsProvider();
    virtual ~TwsProvider();
    void setCallback(FreeQuant::MarketDataProvider::Callback *callback) {}
    void connect(bool block = true);
    void disconnect(bool block = true);
    bool isConnected() const;
    std::string name() const { return "TWS"; }
    void subscribe(std::vector<std::string> symbols);
    void unsubscribe(std::vector<std::string> symbols);
    void currentTime() const;
    void reqHistoricalData(FreeQuant::DateTime startTime, FreeQuant::DateTime endTime);
    void reqFundamentalData(std::string symbol);

private:
    TwsEWrapper *wrapper;
};

} // namespace FreeQuant

#endif // FQ_MARKETDATA_TWSPROVIDER_H
