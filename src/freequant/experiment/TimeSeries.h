#ifndef FQ_EXP_TIMESERIES_H
#define FQ_EXP_TIMESERIES_H

#include <set>
#include <freequant/utils/DateTime.h>

namespace FreeQuant { namespace Exp {

template<typename T>
class TimeSeries {
public:
    typedef std::pair<DateTime, T> Pair;
    struct Comp {
        bool operator()(const Pair& s1, const Pair& s2) const {
            return s1.first < s2.first;
        }
    };
    typedef std::set<Pair, Comp> Set;
    typedef typename Set::iterator Iterator;
    typedef typename Set::const_iterator ConstIterator;

    TimeSeries() {}
    virtual ~TimeSeries() {}
    std::size_t size() const {
        return _data.size();
    }
    DateTime cross(TimeSeries&);

    T& first(long long pos = 1) const {
        double r = pos % size();
        auto i = _data.begin();
        for (r--; r != 0; r--) i++;
        return const_cast<T&>(i->second);
    }

    T& last(long long pos = 1) const {
        double r = pos % size();
        auto i = _data.end();
        for (; r != 0; r--) i--;
        return const_cast<T&>(i->second);
    }

    T& operator[](const DateTime& at) const;
    T& operator[](long long pos) const;

    const DateTime& beginTime() const {
        auto i = _data.begin();
        return i->first;
    }

    const DateTime& endTime() const {
        auto i = _data.end();
        return (i--)->first;
    }

    bool contains(const DateTime&) const;

    void append(const T& value) {
        append(DateTime::now(), value);
    }

    void append(const DateTime& datetime, const T& value) {
        _data.insert(std::make_pair(datetime, value));
    }

    void clear() {
        _data.clear();
    }

    Iterator begin() const { return _data.begin(); }
    Iterator end() const { return _data.end(); }

    T max();
    T min();
    T mean();
    T sum();
    T median();
    T var();
    T sd();
    T moment();
    T kurtosis();
    T skewness();

    friend bool crossesAbove(const TimeSeries&, const TimeSeries&);
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const TimeSeries<U>& dateTime);
private:
    Set _data;

    T _max;
    T _min;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const TimeSeries<T>& dateTime) {
    for (auto i = dateTime.begin(); i != dateTime.end(); ++i) {
        os << i->first << " " << i->second << std::endl;
    }
    return os;
}

}} // namespace FreeQuant

#endif // FQ_EXP_TIMESERIES_H
