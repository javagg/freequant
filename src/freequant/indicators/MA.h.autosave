#ifndef FQ_INDICATORS_MA_H
#define FQ_INDICATORS_MA_H

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/rolling_mean.hpp>

#include <freequant/indicators/Indicator.h>

namespace FreeQuant {

class MA : public Indicator {
public:
    MA() : acc(boost::accumulators::tag::rolling_window::window_size = 5) {}
    void append(double value) {}
    double value() const {
        return boost::accumulators::rolling_mean(acc);
    }

    std::size_t size() { return _data.size(); }
private:
    boost::accumulators::accumulator_set<
        double,
        boost::accumulators::stats<boost::accumulators::tag::rolling_mean>
    > acc;

    std::vector<double> _data;
};

} // namespace FreeQuant

#endif // MA_H
