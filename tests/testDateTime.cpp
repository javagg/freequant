#include <boost/test/unit_test.hpp>

#include <freequant/utils/DateTime.h>

BOOST_AUTO_TEST_CASE(DateTime) {
    FreeQuant::DateTime dt("2012-12-20 23:59:59.000");
    BOOST_CHECK_EQUAL(dt.year(), 2012);
    BOOST_CHECK_EQUAL(dt.month(), 12);
    BOOST_CHECK_EQUAL(dt.day(), 20);
    BOOST_CHECK_EQUAL(dt.hour(), 23);
    BOOST_CHECK_EQUAL(dt.minute(), 59);
    BOOST_CHECK_EQUAL(dt.second(), 59);

    FreeQuant::DateTime d1("2012-12-20 23:59:59.000");
    FreeQuant::DateTime d2("2012-12-20 23:59:59.0");
    FreeQuant::DateTime d3("2012-12-20 23:59:59.100");
    BOOST_CHECK_EQUAL(d1, d2);
    BOOST_CHECK_LT(d2, d3);
}

