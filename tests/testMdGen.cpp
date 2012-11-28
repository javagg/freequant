#include <iostream>
#include <boost/test/unit_test.hpp>

#include <freequant/utils/CsvMarketDataGenerator.h>
#include <freequant/utils/CsvParser.h>
#include <freequant/marketdata/Tick.h>

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

BOOST_AUTO_TEST_CASE(MarketDataGen) {
    using namespace boost::filesystem;
    using namespace FreeQuant;
    CsvMarketDataGenerator gen;
    boost::filesystem::path p = boost::filesystem::current_path();
    p /= "data";
    gen.setDataDir(p.string());
    MarketDataGenerator::Symbols symbols;
    symbols.push_back("IF1212");
    gen.addSymbols(symbols);

    for (int i = 0; i < 3; ++i) {
        MarketDataGenerator::Bars bars = gen.generate();
        if (!bars.empty()) {
            std::cout << bars[0] << std::endl;
        }
    }

//    for (auto di = recursive_directory_iterator(p); di != recursive_directory_iterator(); ++di) {
//        if (is_directory(*di)) {
//            std::cout << (*di).path().filename() << std::endl;
//        } else if (is_regular_file(*di)) {
//           std::cout << (*di).path() << std::endl;
//        }
//    }
}
