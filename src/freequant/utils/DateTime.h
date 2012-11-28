#ifndef FQ_UTILS_DATETIME_H
#define FQ_UTILS_DATETIME_H

#include <ctime>
#include <boost/date_time.hpp>

namespace FreeQuant {

class DateTime {
public:
    DateTime() : _datetime(boost::posix_time::min_date_time) {}
    DateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0,
        long msec = 0) : _datetime(boost::gregorian::date(year, month, day),
        boost::posix_time::time_duration(hour, minute, second)
        + boost::posix_time::milliseconds(msec)) {}
    DateTime(const DateTime& other) : _datetime(other._datetime) {}
    DateTime(const std::time_t& t) : _datetime(boost::posix_time::from_time_t(t)) {}
    DateTime(const std::string& s) : _datetime(boost::posix_time::time_from_string(s)) {}
    DateTime& operator=(const DateTime& other);
    ~DateTime() {}

    DateTime(const std::string& string, const std::string& format);
    int year() const;
    int month() const;
    int day() const;
    int hour() const;
    int minute() const;
    int second() const;
    long msec() const;

    bool valid() const { return !_datetime.is_not_a_date_time(); }

    DateTime& addYears(int years);
    DateTime& addMonths(int months);
    DateTime& addDays(int days);
    DateTime& addHours(int hours);
    DateTime& addMinutes(int minutes);
    DateTime& addSeconds(int seconds);
    DateTime& addMSecs(long msecs);

    static DateTime now();
    bool operator==(const DateTime& other) const { return _datetime == other._datetime; }
    bool operator!=(const DateTime& other) const { return _datetime != other._datetime; }
    bool operator<(const DateTime& other) const { return _datetime < other._datetime; }
    bool operator<=(const DateTime& other) const { return _datetime <= other._datetime; }
    bool operator>(const DateTime& other) const { return _datetime > other._datetime; }
    bool operator>=(const DateTime& other) const { return _datetime >= other._datetime; }

    friend std::ostream& operator<<(std::ostream& out, const DateTime& dateTime);
    friend std::istream& operator>>(std::istream& in, DateTime& dateTime);
private:
    boost::posix_time::ptime _datetime;
};

std::ostream& operator<<(std::ostream& out, const DateTime& dateTime);
std::istream& operator>>(std::istream& in, DateTime& dateTime);

} // namespace FreeQuant

#endif // FQ_UTILS_DATETIME_H
