#include <iostream>

#include <fq/marketdata/provider.h>
#include <fq/marketdata/twsprovider.h>

using namespace FreeQuant::MarketData;

int main(int, char* []) {
    Provider *p =  new TwsProvider();
    p->connect();
    p->disconnect();

    delete p;
    return 0;
}
