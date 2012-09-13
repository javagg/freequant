#include <iostream>

#include <fq/marketdata/marketdataprovider.h>
#include <fq/marketdata/twsprovider.h>

using namespace FreeQuant::MarketData;

int main(int, char* []) {
    MarketDataProvider *p =  new TwsProvider();
    p->connect();
    p->disconnect();

    delete p;
    return 0;
}
