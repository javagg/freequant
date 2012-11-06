#include <iostream>
#include <boost/test/unit_test.hpp>

#include <freequant/indicators/SMA.h>

BOOST_AUTO_TEST_CASE(Indicators) {
    FreeQuant::SMA<5> sma;
    sma.append(19);
    sma.append(19);
    sma.append(19);
    sma.append(19);
    sma.append(19);
}

