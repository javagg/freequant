#include "CsvMarketDataGenerator.h"

#include <functional>
#include <iostream>
#include <random>

namespace FreeQuant {

CsvMarketDataGenerator::CsvMarketDataGenerator(std::string filename) :
    _parser(',', '\n', '\"') {
    _parser.load(filename);
}

}
