#ifndef FQ_UTILS_RANDOMMARKETDATAGENERATOR_H
#define FQ_UTILS_RANDOMMARKETDATAGENERATOR_H

#include <freequant/utils/MarketDataGenerator.h>

namespace FreeQuant {

class RandomMarketDataGenerator : public MarketDataGenerator {
public:
    virtual ~RandomMarketDataGenerator() {}

    virtual std::vector<std::string> availableSymbols() const {
        return std::vector<std::string>();
    }

    FreeQuant::Bar generate(std::string symbol) {
        return FreeQuant::Bar();
    }
};

} // namespace FreeQuant

#endif // FQ_UTILS_RANDOMMARKETDATAGENERATOR_H
