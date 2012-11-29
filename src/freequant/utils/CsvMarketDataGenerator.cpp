#include "CsvMarketDataGenerator.h"

#include <functional>
#include <iostream>
#include <random>

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

namespace FreeQuant {

CsvMarketDataGenerator::CsvMarketDataGenerator(const string& filename) {
//    _parser.load(filename);
}

CsvMarketDataGenerator::CsvMarketDataGenerator() :
    _data_dir("data") {
}

void CsvMarketDataGenerator::addSymbols(const Symbols& symbols) {
    Base::addSymbols(symbols);
    parsers.clear();
    for (auto i = symbols.begin(); i != symbols.end(); ++i) {
        std::shared_ptr<CsvParser> parser(new CsvParser());
        parser->setSkipRows(1);
        boost::filesystem::path p(_data_dir);
        p /= *i + ".txt";
        parser->load(p.string());
        parsers[*i] = parser;
    }
}

void CsvMarketDataGenerator::removeSymbols(const Symbols& symbols) {
    Base::removeSymbols(symbols);
}

void CsvMarketDataGenerator::setDataDir(const string& dir) {
    _data_dir = dir;
}

vector<Bar> CsvMarketDataGenerator::generate() {
    vector<Bar> bars(symbols().size());
    for (auto i = parsers.begin(); i != parsers.end(); ++i) {
        const string& symbol = i->first;
        auto parser = i->second;

        if (parser->hasMore()) {
            auto row = parser->row();
            if (!row.empty()) {
                DateTime dt(row[0]);
                double open = lexical_cast<double>(row[1]);
                double high = lexical_cast<double>(row[2]);
                double low = lexical_cast<double>(row[3]);
                double close = lexical_cast<double>(row[4]);
                long long vol  = lexical_cast<long long>(row[5]);
                Bar bar(symbol, dt, open, high, low, close, vol);
                bars.push_back(bar);
            }
        }
    }
    return bars;
}

}
