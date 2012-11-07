#ifndef FQ_UTILS_TIMESERIES_H
#define FQ_UTILS_TIMESERIES_H

#include <set>
#include <freequant/utils/DateTime.h>

namespace FreeQuant {

template <typename T>
class TimeSeries {
public:
    TimeSeries() {}
    virtual ~TimeSeries() {}
    std::size_t size() const {
        return _data2.size();
    }
    FreeQuant::DateTime cross(TimeSeries&);

    T& first(long long pos = 0) const {
        double r = pos % size();
        auto i = _data2.begin();
        for (; r != 0; r--) i++;
        return const_cast<T&>(i->second);
    }

    T& last(long long pos = 0) {
        double r = pos % size();
        auto i = _data2.end();
        for (; r != 0; r--) i--;
        return const_cast<T&>(i->second);
    }

    T& max();
    T& min();
    T& operator[](const FreeQuant::DateTime& at) const;
    T& operator[](long long pos) const;

    const FreeQuant::DateTime& beginTime() const;
    const FreeQuant::DateTime& endTime() const;
    bool contains(const FreeQuant::DateTime&) const;
    void append(const T& value) {
        append(FreeQuant::DateTime::now(), value);
    }

    void append(const FreeQuant::DateTime& datetime, const T& value) {
//        _data.push_back(std::make_pair(datetime, value));
        _data2.insert(std::make_pair(datetime, value));
    }
//    FreeQuant::TimeSeries& between(const FreeQuant::DateTime<T>& from, const FreeQuant::DateTime<T>& to);
    void remove(int start, int end, bool notify = false);

    void clear() {
        _data2.clear();
    }

    friend bool crossesAbove(const TimeSeries&, const TimeSeries&);
private:
    typedef std::pair<FreeQuant::DateTime, T> Pair;
    struct Comp {
        bool operator()(const Pair& s1, const Pair& s2) const {
            return s1.first < s2.first;
        }
    };
    typedef std::set<Pair, Comp> Set;
    typedef typename Set::iterator Iterator;

    Set _data2;

    T _max;
    T _min;
};

} // namespace FreeQuant

#endif // FQ_UTILS_TIMESERIES_H
