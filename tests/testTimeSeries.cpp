#include <boost/test/unit_test.hpp>

#include <freequant/utils/TimeSeries.h>
#include <freequant/experiment/TimeSeries.h>

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

BOOST_AUTO_TEST_CASE(ExpTimeSeries) {
    FreeQuant::Exp::TimeSeries<double> ts;
    ts.append(FreeQuant::DateTime::now(), 2);
    ts.append(FreeQuant::DateTime::now(), 3);
    ts.append(FreeQuant::DateTime::now(), 4);

    BOOST_CHECK_EQUAL(ts.last(1), 4);
    BOOST_CHECK_EQUAL(ts.last(2), 3);
}
