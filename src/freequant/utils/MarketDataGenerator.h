#ifndef FQ_UTILS_MARKETDATAGENERATOR_H
#define FQ_UTILS_MARKETDATAGENERATOR_H

#include <string>
#include <vector>

#include <freequant/marketdata/Bar.h>

namespace FreeQuant {

class MarketDataGenerator {
public:
    virtual ~MarketDataGenerator() {}
    virtual const std::vector<std::string>& symbols() const = 0;
    virtual void setSymbols(std::vector<std::string>) = 0;
    virtual std::vector<FreeQuant::Bar> generate() = 0;
};

} // namespace FreeQuant

#endif // FQ_UTILS_MARKETDATAGENERATOR_H
