#ifndef FQ_UTILS_YAHOOMARKETDATAGENERATOR_H
#define FQ_UTILS_YAHOOMARKETDATAGENERATOR_H

#include <freequant/utils/RandomMarketDataGenerator.h>
#include <freequant/utils/HttpClient.h>
#include <freequant/utils/CsvParser.h>

namespace FreeQuant {

class YahooMarketDataGenerator : public RandomMarketDataGenerator {
public:
    YahooMarketDataGenerator();
    virtual ~YahooMarketDataGenerator() {}
    Bars generate();
private:
    FreeQuant::Bar generate(std::string symbol);
    FreeQuant::HttpClient _http;
    FreeQuant::CsvParser _parser;
};

} // namespace FreeQuant

#endif // FQ_UTILS_YAHOOMARKETDATAGENERATOR_H
