#ifndef FQ_MDPROVIDERFACTORY_H
#define FQ_MDPROVIDERFACTORY_H

#include <string>

namespace FreeQuant {

class MarketDataProvider;

class MarketDataProviderFactory {
public:
    static MarketDataProvider *createMarketDataProvider(std::string name);
};
}
#endif // FQ_MDPROVIDERFACTORY_H
