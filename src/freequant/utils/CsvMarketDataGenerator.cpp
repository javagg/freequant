#include "CsvMarketDataGenerator.h"

#include <functional>
#include <iostream>
#include <random>

namespace FreeQuant {

CsvMarketDataGenerator::CsvMarketDataGenerator(std::string filename) :
    _parser(',', '\n'), _timer(1000, std::bind(&CsvMarketDataGenerator::generate, this)) {
    _parser.load(filename);
}

void CsvMarketDataGenerator::start() {
    _timer.start();
}

void CsvMarketDataGenerator::stop() {
    _timer.stop();
}

void CsvMarketDataGenerator::generate() {
    Bar bar(100, 100, 99, 90);
    _onGenerated(bar);
}

}
