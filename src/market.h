#ifndef MARKET_H
#define MARKET_H

#include <string>
#include <vector>

namespace FreeQuant {

class Market {
public:
    Market();
    static std::vector<std::string> getAllSymbols(std::string type);

};

}

#endif // MARKET_H
