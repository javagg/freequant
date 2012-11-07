#include <iostream>
#include <boost/test/unit_test.hpp>

#include <freequant/indicators/SMA.h>

#include <freequant/experiment/MA.h>
#include <freequant/experiment/RSI.h>

BOOST_AUTO_TEST_CASE(Indicators) {
    FreeQuant::SMA<5> sma;
    sma.append(19);
    sma.append(19);
    sma.append(19);
    sma.append(19);
    sma.append(19);

    FreeQuant::Exp::RSI rsi;
    FreeQuant::Exp::MA ma(4);
    ma.add(1);
    ma.add(2);
    ma.add(3);
    ma.add(6);
    ma.add(4);
    ma.add(8);
    ma.add(6);

    BOOST_CHECK_EQUAL(ma.last(), 5.25);
    BOOST_CHECK_EQUAL(ma.last(1), 6.0);
}

