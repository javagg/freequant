#ifndef FQ_UTILS_CSVMARKETDATAGENERATOR_H
#define FQ_UTILS_CSVMARKETDATAGENERATOR_H

#include <string>

#include <freequant/utils/RandomMarketDataGenerator.h>
#include <freequant/utils/CsvParser.h>

namespace FreeQuant {

class CsvMarketDataGenerator : public RandomMarketDataGenerator {
public:
    CsvMarketDataGenerator(std::string filename);
    virtual std::vector<FreeQuant::Bar> generate() {
        auto syms = symbols();
        return std::vector<FreeQuant::Bar>();
    }

private:
    FreeQuant::CsvParser _parser;
};

} // namespace FreeQuant

#endif // FQ_UTILS_MARKETDATAGENERATOR_H
