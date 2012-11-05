#ifndef FQ_MDPROVIDERFACTORY_H
#define FQ_MDPROVIDERFACTORY_H

#include <string>

namespace FreeQuant {

class Provider;

class ProviderFactory {
public:
    virtual ~ProviderFactory() {}
    virtual Provider *create() = 0;
    virtual void destroy(Provider *) = 0;
};


}
#endif // FQ_MDPROVIDERFACTORY_H
