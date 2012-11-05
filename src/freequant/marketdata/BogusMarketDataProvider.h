#ifndef FQ_MARKETDATA_BOGUSPROVODER_H
#define FQ_MARKETDATA_BOGUSPROVODER_H

#include <set>
#include <freequant/marketdata/MarketDataProvider.h>
#include <freequant/utils/MarketDataGenerator.h>

namespace FreeQuant {

class BogusMarketDataProvider : public MarketDataProvider {
public:
    explicit BogusMarketDataProvider(MarketDataProvider::Callback *callback = 0) :
        _callback(callback), _connected(false) {}
    ~BogusMarketDataProvider();

    void connect(bool block = true) {
        _connected = true;
        if (_callback) {
            _callback->onConnected();
        }
    }

    void disconnect(bool block = true) {
        _connected = false;
        if (_callback) {
            _callback->onDisconnected();
        }
    }

    bool isConnected() const { return _connected; }
    std::string name() const { return "Bogus"; }
    void subscribe(std::vector<std::string> symbols) {}
    void unsubscribe(std::vector<std::string> symbols) {}
private:
    bool _connected;
    std::set<std::string> _symbols;
    MarketDataProvider::Callback *_callback;
    MarketDataGenerator *_mdGenerator;
};

} // namespace FreeQuant

#endif // FQ_MARKETDATA_BOGUSPROVODER_H
