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
    MA(int window = 10, Bar::BarItem = Bar::BarItemClose) : _window(window), acc(boost::accumulators::tag::rolling_window::window_size = window) {}

    virtual std::size_t size() {
        return _data.size();
    }

    void onCalculate(const Bar& bar) {
//        add(bar.close());
//        if (!values.empty()) {
//            acc(values.front());
//            double calculated = boost::accumulators::rolling_mean(acc);
//            _data.append(datetime, calculated);
//        }
    }

    double last(std::size_t pos = 1) {
        return _data.last(pos);
    }

private:
    Bar::BarItem _barItem;
    TimeSeries<double> _data;
    int _window;
    boost::accumulators::accumulator_set<double,
        boost::accumulators::stats<boost::accumulators::tag::rolling_mean> > acc;

};

}} // namespace FreeQuant

#endif // FQ_EXP_MA_H
