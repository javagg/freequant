#ifndef FQ_UTILS_DATETIME_H
#define FQ_UTILS_DATETIME_H

#include <ctime>
#include <boost/date_time.hpp>

namespace FreeQuant {

class DateTime {
public:
    DateTime() {}
    DateTime(const DateTime& other) : _datetime(other._datetime) {}
    DateTime& operator=(const DateTime& other) {
        if (this != &other) {
            _datetime = other._datetime;
        }
        return *this;
    }
//    DateTime(DateTime&& other);
    DateTime& operator=(DateTime&& other) {
        if (this != &other) {

        }
        return *this;
    }

    DateTime(const std::string&);
    ~DateTime() {}

    DateTime fromString(const std::string& string, const std::string& format);
    DateTime fromTimeT(const std::time_t t);

    int year() const;
    int month() const;
    int day() const;
    int hour() const;
    int minute() const;
    int second() const;
    long long msec() const;

    DateTime& addYears(int years) const;
    DateTime& addMonths(int months) const;
    DateTime& addDays(int days) const;
    DateTime& addHours(int hours) const;
    DateTime& addMinutes(int minutes) const;
    DateTime& addSeconds(int seconds) const;
    DateTime& addMSecs(long long msecs) const;

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
