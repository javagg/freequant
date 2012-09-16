#include <iostream>

#include <fq/marketdata/marketdataprovider.h>
#include <fq/marketdata/yahooprovider.h>

using namespace FreeQuant::MarketData;

int main(int, char* []) {
    MarketDataProvider *p =  new YahooProvider();
    p->connect();
    sleep(10);
    p->disconnect();

    delete p;
    return 0;
}
