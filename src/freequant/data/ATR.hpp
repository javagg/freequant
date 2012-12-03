#ifndef FQ_DATA_ATR_HPP
#define FQ_DATA_ATR_HPP

#include "Indicator.h"
#include "TR.hpp"

namespace FreeQuant { namespace Data {

template <typename DateTime, typename Bar>
class ATR : public Indicator<DateTime, Bar> {
public:
    void onCalculate(const Bar& bar) {
        double prev_value = _data.last();
        double tr = _tr.last();
        double v = (prev_value*13 + tr)/14;
        _data.append(std::make_pair(bar.datetime(), v));
    }
private:
    const static int ma_len = 14;
    TR<DateTime, double> _tr;
    TimeSeries<DateTime, double> _data;
};

}} // namespace FreeQuant

#endif // FQ_DATA_ATR_HPP
