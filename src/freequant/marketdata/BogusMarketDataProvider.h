#ifndef FQ_MARKETDATA_BOGUSPROVODER_H
#define FQ_MARKETDATA_BOGUSPROVODER_H

#include <freequant/marketdata/MarketDataProvider.h>

namespace FreeQuant {

class BogusMarketDataProvider : public MarketDataProvider {
public:
    BogusMarketDataProvider(MarketDataProvider::Callback *callback = 0);
    ~BogusMarketDataProvider();

    void connect(bool block = true) {}
    void disconnect(bool block = true) {}
    bool isConnected() const { return false; }
    std::string name() const { return "Bogus"; }
    void subscribe(std::vector<std::string> symbols) {}
    void unsubscribe(std::vector<std::string> symbols) {}
};

} // namespace FreeQuant

#endif // FQ_MARKETDATA_BOGUSPROVODER_H
