#ifndef FQ_UTILS_YAHOOMARKETDATAGENERATOR_H
#define FQ_UTILS_YAHOOMARKETDATAGENERATOR_H

#include <freequant/utils/MarketDataGenerator.h>
#include <freequant/utils/HttpClient.h>
#include <freequant/utils/CsvParser.h>

namespace FreeQuant {

class YahooMarketDataGenerator : public MarketDataGenerator {
public:
    virtual ~YahooMarketDataGenerator() {}
    virtual std::vector<std::string> availableSymbols();
    FreeQuant::Bar generate(std::string symbol);
private:
    FreeQuant::HttpClient _http;
    FreeQuant::CsvParser _parser;
};

} // namespace FreeQuant

#endif // FQ_UTILS_YAHOOMARKETDATAGENERATOR_H
