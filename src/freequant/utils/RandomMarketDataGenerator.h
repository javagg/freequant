#ifndef FQ_UTILS_RANDOMMARKETDATAGENERATOR_H
#define FQ_UTILS_RANDOMMARKETDATAGENERATOR_H

#include <algorithm>
#include <boost/random.hpp>
#include <freequant/utils/MarketDataGenerator.h>
#include <random>

namespace FreeQuant {

class RandomMarketDataGenerator : public MarketDataGenerator {
public:
    virtual ~RandomMarketDataGenerator() {}

    virtual std::vector<std::string> availableSymbols() const {
        return std::vector<std::string>();
    }

    FreeQuant::Bar generate(std::string symbol) {
        boost::random::uniform_real_distribution<> dist(100,200);
        double open = dist(_rng);
        double close = dist(_rng);
        double high = dist(_rng);
        double low = dist(_rng);
        long volume = static_cast<long>(dist(_rng));
        if (high < low) {
           std::swap(high, low);
        }
        return FreeQuant::Bar(open, high, low, close, volume);
    }

private:
    boost::random::mt19937 _rng;
};

} // namespace FreeQuant

#endif // FQ_UTILS_RANDOMMARKETDATAGENERATOR_H
