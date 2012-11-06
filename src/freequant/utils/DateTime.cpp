#include <boost/date_time.hpp>
#include "DateTime.h"

namespace FreeQuant {

DateTime::DateTime(const std::string& s) :
    _datetime(boost::posix_time::time_from_string(s)) {
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

long long DateTime::msec() const {
//    return _datetime.time_of_day().milliseconds();
    return 0;
}

std::ostream& operator<<(std::ostream& out, const DateTime& dt) {
    return out << dt._datetime;
}

}
