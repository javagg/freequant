#include <iostream>
#include <memory>
#include <thread>

#include <freequant/marketdata/MarketDataProvider.h>
#include <freequant/marketdata/YahooMarketDataProvider.h>
#include <freequant/marketdata/twsprovider.h>

void test_tws() {
    std::shared_ptr<FreeQuant::MarketDataProvider> p(new FreeQuant::TwsProvider());
    p->connect();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    p->disconnect();
}

int main(int, char* []) {
    test_tws();

    return 0;
}
