#include "CsvMarketDataGenerator.h"

#include <functional>

namespace FreeQuant {

CsvMarketDataGenerator::CsvMarketDataGenerator(std::string filename) :
    _parser(',', '\n'), _timer(100, std::function<void()>()) {
    _parser.load(filename);
}

void CsvMarketDataGenerator::start() {
    _timer.start();
}

void CsvMarketDataGenerator::stop() {
    _timer.stop();
}

}
