#ifndef FQ_UTILS_RANDOMMARKETDATAGENERATOR_H
#define FQ_UTILS_RANDOMMARKETDATAGENERATOR_H

#include <algorithm>
#include <boost/random.hpp>
#include <freequant/utils/MarketDataGenerator.h>
#include <random>
#include <set>

namespace FreeQuant {

class RandomMarketDataGenerator : public MarketDataGenerator {
public:
    virtual ~RandomMarketDataGenerator() {}

    const std::vector<std::string>& symbols() const {
        return _symbols;
    }

    void setSymbols(std::vector<std::string> symbols) {
        _symbols = symbols;
    }

    std::vector<FreeQuant::Bar> generate() {
        std::vector<FreeQuant::Bar> bars(_symbols.size());
        for (auto i = _symbols.begin(); i !=_symbols.end(); i++) {
            bars.push_back(generate(*i));
        }
        return bars;
    }

private:
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
        return FreeQuant::Bar(symbol, FreeQuant::DateTime(), open, high, low, close, volume);
    }

    boost::random::mt19937 _rng;
    std::vector<std::string> _symbols;
};

} // namespace FreeQuant

#endif // FQ_UTILS_RANDOMMARKETDATAGENERATOR_H
