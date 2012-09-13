#include <iostream>

#include <fq/marketdata/marketdataprovider.h>
#include <fq/marketdata/ctp/ctpmarketdataprovider.h>
#include <fq/trade/ctptradeprovider.h>
#include <boost/thread.hpp>

int main(int, char* []) {
    FreeQuant::MarketData::MarketDataProvider *p = new FreeQuant::MarketData::CtpMarketDataProvider();
    p->connect();
    boost::this_thread::sleep(boost::posix_time::seconds(2));
    p->disconnect();
    delete p;

    return 0;
}
