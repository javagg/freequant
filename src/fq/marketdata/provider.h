#ifndef FQ_MARKETDATA_PROVIDER_H
#define FQ_MARKETDATA_PROVIDER_H

#include <string>

namespace FreeQuant { namespace MarketData {

class Provider {
public:
    virtual ~Provider() {}
    virtual void connect() = 0;
    virtual void disconnect() = 0;
    virtual bool isConnected() const = 0;
    virtual std::string name() const = 0;
};

}}

#endif //FQ_MARKETDATA_PROVIDER_H
