#include <iostream>

#include <fq/marketdata/provider.h>
#include <fq/trade/provider.h>
#include <fq/marketdata/ctp/ctpprovider.h>
#include <fq/trade/ctpprovider.h>
#include <boost/thread.hpp>

int main(int, char* []) {
    FreeQuant::MarketData::Provider *p1 = new FreeQuant::MarketData::CtpProvider();
//    p->connect();
//    boost::this_thread::sleep(boost::posix_time::seconds(2));
//    p->disconnect();
//    delete p;

    FreeQuant::Trade::Provider *p2 = new FreeQuant::Trade::CtpProvider();
//    p->connect();
//    boost::this_thread::sleep(boost::posix_time::seconds(2));
//    p->disconnect();
//    delete p;

    return 0;
}
