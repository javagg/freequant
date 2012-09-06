#ifndef FQ_MARKETDATA_PROVIDER_H
#define FQ_MARKETDATA_PROVIDER_H

#include <string>

namespace FreeQuant { namespace MarketData {

class Provider {
public:
    explicit Provider();
    virtual ~Provider();
    void connect();
    void disconnect();
    bool isConnected();

    std::string name();
};

}}

#endif //FQ_MARKETDATA_PROVIDER_H
