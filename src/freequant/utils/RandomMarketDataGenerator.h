#ifndef FQ_UTILS_RANDOMMARKETDATAGENERATOR_H
#define FQ_UTILS_RANDOMMARKETDATAGENERATOR_H

#include <algorithm>
#include <random>
#include <set>

//#include <boost/random.hpp>
#include <freequant/utils/MarketDataGenerator.h>

namespace FreeQuant {

class RandomMarketDataGenerator : public MarketDataGenerator {
public:
    virtual ~RandomMarketDataGenerator() {}
    const Symbols& symbols() const { return _symbols; }
    void addSymbols(const Symbols&);
    void removeSymbols(const Symbols&);
    Bars generate();

private:
    std::mt19937 _rng;
    Symbols _symbols;
};

} // namespace FreeQuant

#endif // FQ_UTILS_RANDOMMARKETDATAGENERATOR_H
