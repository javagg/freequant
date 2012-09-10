#ifndef FQ_TRADE_PROVIDER_H
#define FQ_TRADE_PROVIDER_H

namespace FreeQuant { namespace Trade {

class Provider {
public:
    virtual void connect() = 0;
    virtual void disconnect() = 0;
    virtual bool isConnected() const = 0;
    virtual std::string name() const = 0;
};

}}

#endif // FQ_TRADE_PROVIDER_H
