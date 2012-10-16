#ifndef FQ_MARKETDATA_TWSPROVIDER_H
#define FQ_MARKETDATA_TWSPROVIDER_H

#include <string>

#include <freequant/marketdata/marketdataprovider.h>
#include <freequant/utils/datetime.h>

namespace FreeQuant {

class TwsEWrapper;

class TwsProvider : public MarketDataProvider {
public:
    TwsProvider();
    virtual ~TwsProvider();
    virtual void connect(bool block = true);
    virtual void disconnect(bool block = true);
    virtual bool isConnected() const;
    virtual std::string name() const { return "TWS"; }
    virtual void subscribe(std::vector<std::string> symbols);
    virtual void unsubscribe(std::vector<std::string> symbols);
    virtual void currentTime() const;
    virtual void reqHistoricalData(FreeQuant::DateTime startTime, FreeQuant::DateTime endTime);
    virtual void reqFundamentalData(std::string symbol);

    void onConnected() {}
    void onDisconnected() {}
    void onBar(FreeQuant::Bar&) {}

private:
    TwsEWrapper *wrapper;
};

} // namespace FreeQuant

#endif // FQ_MARKETDATA_TWSPROVIDER_H
