#ifndef FQ_DATA_BB_H
#define FQ_DATA_BB_H

#include "Indicator.h"

namespace FreeQuant { namespace Data {

template <typename DateTime, typename Bar>
class BB : public Indicator<DateTime, Bar> {
public:
    void onCalculate(const Bar& bar) {
//        double prev_value = _data.last();
//        double tr = _tr.last();
//        double v = (prev_value*13 + tr)/14;
//        _data.append(std::make_pair(bar.datetime(), v));
    }
private:
    TimeSeries<DateTime, double, double, double> _data;
};


}} // namespace FreeQuant


#endif // # FQ_DATA_MA_H
