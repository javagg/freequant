#include <iostream>

#include <boost/test/prg_exec_monitor.hpp>
//#include <boost/test/included/prg_exec_monitor.hpp>
//#include <boost/asio.hpp>

#include <fq/marketdata/provider.h>
#include <fq/marketdata/csv/csvprovider.h>

using namespace FreeQuant::MarketData;

int cpp_main(int, char* []) {
    std::cout << "Hello, world\n";

    Provider *p =  new CsvProvider();
    p->connect();
    sleep(10);
    p->disconnect();

    delete p;
    return 0;
}
