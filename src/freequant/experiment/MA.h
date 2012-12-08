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

    std::size_t size() const {
        return _data.size();
    }

    void onCalculate(const Bar& bar) {
        double value = bar.close();
        acc(value);
        double calculated = boost::accumulators::rolling_mean(acc);
        append(bar.dateTime(), calculated);
    }

    double last(std::size_t pos = 1, int which = 0) {
        return _data.last(pos);
    }

    void append(const DateTime& datetime, double value, int which = 0) {
        _data.append(datetime, value);
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
