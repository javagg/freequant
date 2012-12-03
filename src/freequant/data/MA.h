#ifndef FQ_DATA_MA_H
#define FQ_DATA_MA_H

#include <vector>
#include <limits>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/rolling_mean.hpp>

#include "Indicator.h"
#include "TimeSeries.hpp"

namespace FreeQuant { namespace Data {

template <typename DateTime, typename Bar>
class MA : public Indicator<DateTime, Bar> {
public:
    typedef typename Indicator<DateTime, Bar>::MaMethod MaMethod;

    MA(int window = 10, MaMethod method = Indicator<DateTime, Bar>::SMA) : _window(window), acc(boost::accumulators::tag::rolling_window::window_size = window) {}

    virtual std::size_t size() {
        return _data.size();
    }

    void add(const DateTime& datetime, const std::map<std::string, double>& values) {

    }

    void onCalculate(const Bar& bar);

    void add(const DateTime& datetime, std::vector<double>& values) {
        if (!values.empty()) {
            acc(values.front());
            double calculated = boost::accumulators::rolling_mean(acc);
            _data.append(datetime, calculated);
        }
    }

    void add(double value) {
        std::vector<double> v;
        v.push_back(value);
        add(v);
    }

    double last(const std::string& column, std::size_t pos = 1) {
        return _data.last(pos);
    }

    double last(long long pos = 1) {
        return _data.last(pos);
    }

private:
    TimeSeries<DateTime, double> _data;
    int _window;
    boost::accumulators::accumulator_set<double,
        boost::accumulators::stats<boost::accumulators::tag::rolling_mean> > acc;
};

}}
#endif // FQ_DATA_MA_H

