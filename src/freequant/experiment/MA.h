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
    MA(int window = 10, Bar::BarItem barItem = Bar::BarItemClose) :
        _window(window), _barItem(barItem),
        acc(boost::accumulators::tag::rolling_window::window_size = window) {}

    virtual std::size_t size() {
        return _data.size();
    }

    void onCalculate(const Bar& bar) {
        double value = bar.close();
        acc(value);
        double calculated = boost::accumulators::rolling_mean(acc);
        _data.append(bar.dateTime(), calculated);
    }

    double last(int which = 0, std::size_t pos = 1) const {
        return _data.last(pos);
    }

private:
    int _window;
    Bar::BarItem _barItem;
    TimeSeries<double> _data;
    boost::accumulators::accumulator_set<double,
        boost::accumulators::stats<boost::accumulators::tag::rolling_mean> > acc;

};

}} // namespace FreeQuant

#endif // FQ_EXP_MA_H
