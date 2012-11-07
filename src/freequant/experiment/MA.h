#ifndef FQ_EXP_MA_H
#define FQ_EXP_MA_H

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

    void add(const FreeQuant::DateTime& datetime, const std::map<std::string, double>& values) {
//        _data.append(datetiem, values);
    }

    void add(const FreeQuant::DateTime& datetime, std::vector<double>& values) {
        if (!values.empty()) {
            double calculated = values[0];
            acc(calculated);
            _data.append(datetime, boost::accumulators::rolling_mean(acc));
        }
    }

    void add(std::vector<double>& values) {
        add(FreeQuant::DateTime::now(), values);
    }

    void add(double value) {
        std::vector<double> v(1);
        v.push_back(value);
        add(v);
    }

    double last(const std::string& column, long long pos = 0) {
        return _data.last(pos);
    }

    double last(long long pos = 0) {
        return _data.last(pos);
    }

private:
    FreeQuant::TimeSeries<double> _data;
    int _window;
    boost::accumulators::accumulator_set<double,
        boost::accumulators::stats<boost::accumulators::tag::rolling_mean> > acc;

};

}} // namespace FreeQuant

#endif // FQ_EXP_MA_H
