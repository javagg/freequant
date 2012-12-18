#ifndef FQ_UTILS_TIMESERIES_H
#define FQ_UTILS_TIMESERIES_H

#include <set>

#include <freequant/utils/DateTime.h>

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

namespace FreeQuant {

template <typename T>
class TimeSeries {
public:
    TimeSeries() {}
    virtual ~TimeSeries() {}
    std::size_t size() const {
        return _data.size();
    }
    DateTime cross(TimeSeries&);

    T& first(long long pos = 1) const {
        long long r = pos % size();
        auto i = _data.begin();
        for (; r != 0; r--) i++;
        return const_cast<T&>(i->second);
    }

    T& last(long long pos = 1) {
        long long r = pos % size();
        auto i = _data.end();
        for (; r != 0; r--) i--;
        return const_cast<T&>(i->second);
    }

    T& max() { return _max; }
    T& min() { return _min; }
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
//    FreeQuant::TimeSeries& between(const FreeQuant::DateTime<T>& from, const FreeQuant::DateTime<T>& to);
    void remove(int start, int end, bool notify = false);

    void clear() {
        _data.clear();
    }

    friend bool crossesAbove(const TimeSeries&, const TimeSeries&);
private:
    typedef std::pair<DateTime, T> Pair;
    struct Comp {
        bool operator()(const Pair& s1, const Pair& s2) const {
            return s1.first < s2.first;
        }
    };
    typedef std::set<Pair, Comp> Set;
    typedef typename Set::iterator Iterator;

    Set _data;

    T _max;
    T _min;
};

} // namespace FreeQuant

#endif // FQ_UTILS_TIMESERIES_H
