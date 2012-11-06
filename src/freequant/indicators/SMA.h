#ifndef FQ_INDICATORS_SMA_H
#define FQ_INDICATORS_SMA_H

#include <vector>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/rolling_mean.hpp>

#include <freequant/indicators/Indicator.h>

namespace FreeQuant {

template<typename std::size_t Window>
class SMA : public Indicator {
public:
    SMA() : _acc(boost::accumulators::tag::rolling_window::window_size = Window) {}
    double value() const {
        return boost::accumulators::rolling_mean(_acc);
    }

    void append(double v) {
        _data.push_back(v);
        _acc(_data.back());
    }

    std::size_t size() { return _data.size(); }
private:
    boost::accumulators::accumulator_set<
        double,
        boost::accumulators::stats<boost::accumulators::tag::rolling_mean>
    > _acc;
    std::vector<double> _data;
};

}
#endif // FQ_INDICATORS_SMA_H
