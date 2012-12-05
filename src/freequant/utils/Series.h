#ifndef FQ_UTILS_SERIES_H
#define FQ_UTILS_SERIES_H

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
class Series {
public:
    Series() {}

    std::size_t size() const {
        return _data.size();
    }

//    DateTime cross(TimeSeries&);

    T& first(std::size_t pos = 1) const {
        auto r = pos % size();
        auto i = _data.begin();
        for (; r != 0; r--) i++;
        return const_cast<T&>(i->second);
    }

    T& last(std::size_t pos = 1) {
        long long r = pos % size();
        auto i = _data.end();
        for (; r != 0; r--) i--;
        return const_cast<T&>(i->second);
    }

    T& max() { return _max; }
    T& min() { return _min; }
    T& operator[](const DateTime& at) const;
    T& operator[](std::size_t pos) const;

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

    void clear() {
        _data.clear();
    }

private:
    typedef std::pair<DateTime, T> Pair;
//    struct Comp {
//        bool operator()(const Pair& s1, const Pair& s2) const {
//            return s1.first < s2.first;
//        }
//    };
    typedef std::set<Pair, Comp> Set;
    typedef typename Set::iterator Iterator;

    Set _data;

    T _max;
    T _min;
};

} // namespace FreeQuant

#endif // FQ_UTILS_TIMESERIES_H
