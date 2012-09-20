#ifndef FQ_MARKETDATA_MARKETDATAPROVIDER_H
#define FQ_MARKETDATA_MARKETDATAPROVIDER_H

#include <string>
#include <vector>

namespace FreeQuant { namespace MarketData {

class MarketDataProvider {
public:
    virtual ~MarketDataProvider() {}
    virtual void connect() = 0;
    virtual void disconnect() = 0;
    virtual bool isConnected() const = 0;
    virtual std::string name() const = 0;
    virtual void subscribe(std::vector<std::string> symbols) = 0;
    virtual void unsubscribe(std::vector<std::string> symbols) = 0;
    virtual void testMe() {}
};

}}

#endif //FQ_MARKETDATA_MARKETDATAPROVIDER_H
