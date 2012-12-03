#ifndef FQ_DATA_TIMESERIES_HPP
#define FQ_DATA_TIMESERIES_HPP

#include <vector>

namespace FreeQuant { namespace Data {

template <typename DT, typename T>
class TimeSeries {
public:
    typedef DT datetime_type;
    typedef T value_type;
    typedef std::vector<value_type> Data;
//    typedef typename Data::size_type size_type;

    std::size_t size() const { return _data.size(); }

    void append(const T& value) {
        _data.push_back(value);
    }

    void clear() { _data.clear(); }

    void remove(std::size_t n) {}

    const DT& beginTime() const {

    }

    const DT& endTime() const {

    }

    T& last() const {
        return _data[0];
    }

    T& first() const {
        return _data[size()-1];
    }

    T& operator[](std::size_t n) {
        return _data[n];
    }

    bool contains(const T& value) {
        return false;
    }

    std::size_t position(const DT& datetime) const {
        return 0;
    }

private:
    std::vector<T> _data;
    std::vector<std::pair<DT, T> > _data1;
};

}}
#endif // FQ_DATA_TIMESERIES_HPP
