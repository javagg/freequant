#ifndef FQ_PROVIDER_H
#define FQ_PROVIDER_H

#include <stdexcept>

namespace FreeQuant {

class Provider {
public:
    virtual ~Provider() {}
    virtual void connect(bool block = true) = 0;
    virtual void disconnect(bool block = true) = 0;
    virtual bool isConnected() const = 0;
    virtual std::string name() const = 0;
};

}

#endif // FQ_PROVIDER_H
