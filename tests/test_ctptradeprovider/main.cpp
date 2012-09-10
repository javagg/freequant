#include <iostream>

#include <fq/trade/tradeprovider.h>
#include <fq/trade/ctptradeprovider.h>
#include <boost/thread.hpp>

int main(int, char* []) {
    FreeQuant::Trade::TradeProvider *p = new FreeQuant::Trade::CtpTradeProvider();
    p->connect();
    boost::this_thread::sleep(boost::posix_time::seconds(2));
    p->disconnect();
    delete p;

    return 0;
}
