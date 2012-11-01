#ifndef FQ_UTILS_MARKETDATAGENERATOR_H
#define FQ_UTILS_MARKETDATAGENERATOR_H

#include <string>
#include <vector>

#include <freequant/marketdata/Bar.h>

namespace FreeQuant {

class MarketDataGenerator {
public:
    typedef std::vector<std::string> Symbols;
    typedef std::vector<FreeQuant::Bar> Bars;

    virtual ~MarketDataGenerator() {}
    virtual const Symbols& symbols() const = 0;
    virtual void addSymbols(Symbols&) = 0;
    virtual void removeSymbols(Symbols&) = 0;
    virtual Bars generate() = 0;
};

} // namespace FreeQuant

#endif // FQ_UTILS_MARKETDATAGENERATOR_H
