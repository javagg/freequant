#include <iostream>
#include <memory>
#include <boost/thread.hpp>

#include <freequant/marketdata/MarketDataProvider.h>
#include <freequant/marketdata/YahooMarketDataProvider.h>
#include <freequant/trade/TwsTradeProvider.h>
#include <freequant/utils/CsvParser.h>
#include <freequant/marketdata/twsprovider.h>

void test_tws() {
    boost::shared_ptr<FreeQuant::MarketDataProvider> p(new FreeQuant::TwsProvider());
    p->connect();
    boost::this_thread::sleep_for(boost::chrono::seconds(5));
    p->disconnect();
}

void test_ib() {
    boost::shared_ptr<FreeQuant::TradeProvider> p(new FreeQuant::TwsTradeProvider());
    p->connect();
    boost::this_thread::sleep_for(boost::chrono::seconds(5));
    p->disconnect();
}

void test_csv() {
//    FreeQuant::CsvParser parser;
//    parser.load("test.csv");
//    while (parser.hasMore()) {
//        std::vector<std::string> row = parser.row();
//        std::copy(row.begin(), row.end(), ostream_iteratr<string>(cout, " "));
//    }
}

int main(int, char* []) {
//    test_tws();
    test_ib();
    test_csv();
    return 0;
}
