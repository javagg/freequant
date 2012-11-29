#include <iostream>
#include <boost/test/unit_test.hpp>
#include <vector>
#include <freequant/marketdata/TickCompressor.h>
#include <freequant/marketdata/Tick.h>
#include <freequant/marketdata/Bar.h>

using namespace std;
using namespace FreeQuant;

BOOST_AUTO_TEST_CASE(Compressor) {
    TickCompressor<Tick, Bar> compressor([](const std::vector<Tick>& ticks) {
        copy(ticks.begin(), ticks.end(), ostream_iterator<Tick>(cout, "\n"));
    });
    Tick tick1, tick2, tick3, tick4, tick5, tick6, tick7;
    tick1.datetime = DateTime("2012-12-12 09:10:01");
    tick2.datetime = DateTime("2012-12-12 09:10:05");
    tick3.datetime = DateTime("2012-12-12 09:11:11");
    tick4.datetime = DateTime("2012-12-12 09:11:31");
    tick5.datetime = DateTime("2012-12-12 09:11:51");
    tick6.datetime = DateTime("2012-12-12 09:11:57");
    tick7.datetime = DateTime("2012-12-12 09:12:01");
    Tick ticks[] = {tick1, tick2, tick3, tick4, tick5, tick6, tick7};
    vector<Tick> v(ticks, ticks+7);
    for (auto i = v.begin(); i != v.end(); ++i) {
        compressor.compress(*i);
    }
}

