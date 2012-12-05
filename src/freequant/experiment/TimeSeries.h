#ifndef FQ_EXP_TIMESERIES_H
#define FQ_EXP_TIMESERIES_H

#include <set>
#include <freequant/utils/DateTime.h>

namespace FreeQuant { namespace Exp {

template<typename T>
class TimeSeries {
public:
    std::size_t size() const {
        return _data.size();
    }

    T& operator[](std::size_t pos) {
        return _data[pos].second;
    }

    T& last(std::size_t pos = 1) {
        return _data[_data.size()-pos].second;
    }

    T& operator[](const DateTime& dt) const;

    const DateTime& beginTime() const {
        auto i = _data.begin();
        return i->first;
    }

    const DateTime& endTime() const {
        auto i = _data.end();
        return (i--)->first;
    }

    bool contains(const DateTime& dt) const {
        auto i = find_if(_data.begin(), _data.end(), [&](std::pair<DateTime, T>& pair) {
            return pair.first == dt;
        });
        return i != _data.end();
    }

    void append(const DateTime& datetime, const T& value) {
        _data.push_back(std::make_pair(datetime, value));
    }

    void clear() {
        _data.clear();
    }

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

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const TimeSeries<U>& dateTime);
private:
    std::vector<std::pair<DateTime, T> > _data;
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
