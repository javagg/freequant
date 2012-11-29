#ifndef FQ_UTILS_CSVMARKETDATAGENERATOR_H
#define FQ_UTILS_CSVMARKETDATAGENERATOR_H

#include <string>

#include <freequant/utils/RandomMarketDataGenerator.h>
#include <freequant/utils/CsvParser.h>

namespace FreeQuant {

class CsvMarketDataGenerator : public RandomMarketDataGenerator {
public:
    CsvMarketDataGenerator(const std::string& filename);
    explicit CsvMarketDataGenerator();
    virtual std::vector<Bar> generate();
    void addSymbols(const Symbols&);
    void removeSymbols(const Symbols&);
    void setDataDir(const std::string& dir);
private:
    typedef RandomMarketDataGenerator Base;
//    CsvParser _parser;
    std::string _data_dir;
    std::map<std::string, std::shared_ptr<CsvParser> > parsers;
};

} // namespace FreeQuant

#endif // FQ_UTILS_MARKETDATAGENERATOR_H
