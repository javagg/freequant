#include <iostream>
#include <memory>
#include <boost/thread.hpp>

#include <freequant/marketdata/MarketDataProvider.h>
#include <freequant/marketdata/YahooMarketDataProvider.h>
#include <freequant/marketdata/twsprovider.h>

void test_tws() {
    boost::shared_ptr<FreeQuant::MarketDataProvider> p(new FreeQuant::TwsProvider());
    p->connect();
    boost::this_thread::sleep_for(boost::chrono::seconds(1));
    p->disconnect();
}

int main(int, char* []) {
    test_tws();

    return 0;
}
