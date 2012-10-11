#include <iostream>
#include <memory>
#include <thread>

#include <fq/marketdata/marketdataprovider.h>
#include <fq/marketdata/yahooprovider.h>
#include <fq/marketdata/twsprovider.h>

using namespace FreeQuant::MarketData;

void test_tws() {
    std::shared_ptr<MarketDataProvider> p(new TwsProvider());
    p->connect();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    p->disconnect();
}

int main(int, char* []) {
    test_tws();

    return 0;
}
