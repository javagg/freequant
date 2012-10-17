#ifndef FQ_UTILS_MARKETDATAGENERATOR_H
#define FQ_UTILS_MARKETDATAGENERATOR_H

#include <string>
#include <vector>

#include <freequant/marketdata/Bar.h>

namespace FreeQuant {

class MarketDataGenerator {
public:
    virtual ~MarketDataGenerator() {}
    virtual std::vector<std::string> availableSymbols() const = 0;
    virtual FreeQuant::Bar generate(std::string symbol) = 0;
};

} // namespace FreeQuant

#endif // FQ_UTILS_MARKETDATAGENERATOR_H
