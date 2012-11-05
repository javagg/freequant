#include <vector>
#include "RandomMarketDataGenerator.h"

using namespace std;

namespace FreeQuant {

MarketDataGenerator::Bars RandomMarketDataGenerator::generate() {
    std::uniform_real_distribution<> dist(100,200);
    vector<Bar> bars(_symbols.size());
    for (auto i = _symbols.begin(); i != _symbols.end(); ++i) {
        double open = dist(_rng);
        double close = dist(_rng);
        double high = dist(_rng);
        double low = dist(_rng);
        long volume = static_cast<long>(dist(_rng));
        if (high < low) {
           std::swap(high, low);
        }
        bars.push_back(Bar(*i, DateTime(), open, high, low, close, volume));
    }
    return bars;
}

void RandomMarketDataGenerator::addSymbols(Symbols& symbols) {
    set<string> s(_symbols.begin(), _symbols.end());
    s.insert(symbols.begin(), symbols.end());
    _symbols.clear();
    _symbols.insert(_symbols.end(), s.begin(), s.end());
}

void RandomMarketDataGenerator::removeSymbols(Symbols& symbols) {
    for (auto i = symbols.begin(); i != symbols.end(); ++i) {
        remove(_symbols.begin(), _symbols.end(), *i);
    }
//    sort(_symbols.begin(), _symbols.end());
//    sort (symbols.begin(), symbols.end());
//    Symbols result(_symbols.size() + symbols.size());
//    set_difference(_symbols.begin(),_symbols.end(), symbols.begin(),symbols.end(),
//        back_insert_iterator<Symbols>(result));
//    _symbols.clear();
//    copy(result.begin(), result.end(), _symbols.begin());
}

} // namespace FreeQuant
