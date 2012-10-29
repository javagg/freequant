#include "CsvMarketDataGenerator.h"

#include <functional>
#include <iostream>
#include <random>

namespace FreeQuant {

CsvMarketDataGenerator::CsvMarketDataGenerator(std::string filename) :
    _parser(',', '\n') {
    _parser.load(filename);
}

std::vector<std::string> CsvMarketDataGenerator::availableSymbols() const {
    return std::vector<std::string>();
}

FreeQuant::Bar CsvMarketDataGenerator::generate(std::string symbol) {
    return FreeQuant::Bar(1,1,1,1,1);
}

}
