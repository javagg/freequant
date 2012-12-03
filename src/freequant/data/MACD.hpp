#ifndef FQ_DATA_MACD_HPP
#define FQ_DATA_MACD_HPP

#include "Indicator.h"
#include "MA.h"

namespace FreeQuant { namespace Data {

template <typename DateTime, typename Bar>
class MACD : public Indicator<DateTime, Bar> {
public:
    void onCalculate(const Bar& bar) {
//        double prev_value = _data.last();
//        double tr = _tr.last();
//        double v = (prev_value*13 + tr)/14;
//        _data.append(std::make_pair(bar.datetime(), v));
    }
private:
    int _short;
    int _long;
    int _N;

    int _curIdx;
    double _latestValue;
    MA<DateTime, double> _ma12;
    MA<DateTime, double> _ma26;
    MA<DateTime, double> _signal;

    TimeSeries<DateTime, double> _dif;
    TimeSeries<DateTime, double> _dea;
    TimeSeries<DateTime, double> _data;
};

}} // namespace FreeQuant


#endif // FQ_DATA_MACD_HPP
