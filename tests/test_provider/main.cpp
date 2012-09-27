#include <iostream>

#include <boost/thread.hpp>
#include <fq/marketdata/marketdataprovider.h>
#include <fq/marketdata/yahooprovider.h>
#include <fq/marketdata/twsprovider.h>

using namespace FreeQuant::MarketData;

void test_tws() {
    MarketDataProvider *p =  new TwsProvider();
    p->connect();
    boost::this_thread::sleep(boost::posix_time::seconds(1));
    p->disconnect();

    delete p;
}

int main(int, char* []) {
    test_tws();

    return 0;
}
