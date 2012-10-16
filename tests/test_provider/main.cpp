#include <iostream>
#include <memory>
#include <thread>

#include <freequant/marketdata/marketdataprovider.h>
#include <freequant/marketdata/yahooprovider.h>
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
