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

//    static MarketDataProvider *createMarketDataProvider(std::string name);
};


}
#endif // FQ_MDPROVIDERFACTORY_H
