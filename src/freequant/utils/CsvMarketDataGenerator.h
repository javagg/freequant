#ifndef FQ_UTILS_CSVMARKETDATAGENERATOR_H
#define FQ_UTILS_CSVMARKETDATAGENERATOR_H

#include <string>

#include <freequant/utils/MarketDataGenerator.h>
#include <freequant/utils/Timer.h>
#include <freequant/utils/CsvParser.h>

namespace FreeQuant {

class CsvMarketDataGenerator : public MarketDataGenerator {
public:
    CsvMarketDataGenerator(std::string filename);
    virtual ~CsvMarketDataGenerator() {}
    virtual void start();
    virtual void stop();
    virtual std::vector<std::string> availableSymbols() const {
        return std::vector<std::string>();
    }

private:
    FreeQuant::Timer _timer;
    FreeQuant::CsvParser _parser;
    void generate();
};

} // namespace FreeQuant

#endif // FQ_UTILS_MARKETDATAGENERATOR_H
