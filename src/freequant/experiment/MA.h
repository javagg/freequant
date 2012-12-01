#ifndef FQ_EXP_MA_H
#define FQ_EXP_MA_H

#include <vector>
#include <limits>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/rolling_mean.hpp>

#include <freequant/experiment/Indicator.h>

namespace FreeQuant { namespace Exp {

class MA : public Indicator {
public:
    MA(int window = 10) : _window(window), acc(boost::accumulators::tag::rolling_window::window_size = window) {}
    ~MA() {}
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

    void add(std::vector<double>& values) {
        add(DateTime::now(), values);
    }

    void add(double value) {
        std::vector<double> v;
        v.push_back(value);
        add(v);
    }

    double last(const std::string& column, long long pos = 1) {
        return _data.last(pos);
    }

    double last(long long pos = 1) {
        return _data.last(pos);
    }

private:
    TimeSeries<double> _data;
    int _window;
    boost::accumulators::accumulator_set<double,
        boost::accumulators::stats<boost::accumulators::tag::rolling_mean> > acc;

};

}} // namespace FreeQuant

#endif // FQ_EXP_MA_H
