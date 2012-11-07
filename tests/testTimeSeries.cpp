#include <boost/test/unit_test.hpp>

#include <freequant/utils/TimeSeries.h>

BOOST_AUTO_TEST_CASE(TimeSeries) {
    FreeQuant::TimeSeries<double> ts;
    ts.append(1);
    ts.append(2);
    BOOST_CHECK_EQUAL(ts.size(), 2);

    ts.clear();
    FreeQuant::DateTime dt1("2012-12-12");
    FreeQuant::DateTime dt2("2012-12-13");
    ts.append(dt2, 100);
    ts.append(dt1, 20);
    BOOST_CHECK_EQUAL(ts.last(), 100);
    BOOST_CHECK_EQUAL(ts.last(1), 20);

    BOOST_CHECK_EQUAL(ts.beginTime(), FreeQuant::DateTime("2012-12-12"));
    BOOST_CHECK_EQUAL(ts.endTime(), FreeQuant::DateTime("2012-12-13"));
}
