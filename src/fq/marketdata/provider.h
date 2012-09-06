#ifndef FQ_MARKETDATA_PROVIDER_H
#define FQ_MARKETDATA_PROVIDER_H

#include <string>

namespace FreeQuant { namespace MarketData {

class Provider {
public:
    explicit Provider();
    virtual ~Provider();
    virtual void connect() = 0;
    virtual void disconnect() = 0;
    virtual bool isConnected() = 0;

    std::string name();
};

}}

#endif //FQ_MARKETDATA_PROVIDER_H
