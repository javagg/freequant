#include <sstream>
#include <boost/date_time.hpp>
#include "DateTime.h"

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

namespace FreeQuant {

DateTime::DateTime(const std::string& s, const std::string& format) {
    stringstream ss;
    time_input_facet *f = new time_input_facet(format);
    ss.imbue(std::locale(ss.getloc(), f));
    ss.str(s);
    ss >> _datetime;
}

DateTime& DateTime::operator=(const DateTime& other) {
    if (this != &other) {
        _datetime = other._datetime;
    }
    return *this;
}

int DateTime::year() const {
    return  _datetime.date().year();
}

int DateTime::month() const {
    return  _datetime.date().month();
}

int DateTime::day() const {
    return  _datetime.date().day();
}

int DateTime::hour() const {
    return _datetime.time_of_day().hours();
}

int DateTime::minute() const {
    return _datetime.time_of_day().minutes();
}

int DateTime::second() const {
    return _datetime.time_of_day().seconds();
}

long DateTime::msec() const {
    boost::posix_time::time_duration td = _datetime.time_of_day();
    return static_cast<long>(td.total_milliseconds() - td.total_seconds()*1000);
}

DateTime::WeekDays DateTime::dayOfWeek() const {
    return static_cast<WeekDays>(_datetime.date().day_of_week());
}

int DateTime::dayOfYear() const {
    return static_cast<int>(_datetime.date().day_of_year());
}

DateTime DateTime::now() {
    DateTime dt;
    dt._datetime = boost::posix_time::microsec_clock::local_time();
    return dt;
}

DateTime& DateTime::addYears(int years) {
    boost::gregorian::date d = _datetime.date() + boost::gregorian::years(years);
    _datetime = boost::posix_time::ptime(d, _datetime.time_of_day());
    return *this;
}

DateTime& DateTime::addMonths(int months) {
    boost::gregorian::date d = _datetime.date() + boost::gregorian::months(months);
    _datetime = boost::posix_time::ptime(d, _datetime.time_of_day());
    return *this;
}

DateTime& DateTime::addDays(int days) {
    boost::gregorian::date d = _datetime.date() + boost::gregorian::days(days);
    _datetime = boost::posix_time::ptime(d, _datetime.time_of_day());
    return *this;
}

DateTime& DateTime::addHours(int hours) {
    _datetime += boost::posix_time::hours(hours);
    return *this;
}

DateTime& DateTime::addMinutes(int minutes) {
    _datetime += boost::posix_time::minutes(minutes);
    return *this;
}

DateTime& DateTime::addSeconds(int seconds) {
    _datetime += boost::posix_time::seconds(seconds);
    return *this;
}

DateTime& DateTime::addMSecs(long msecs) {
    _datetime += boost::posix_time::milliseconds(msecs);
    return *this;
}

}
