#ifndef FQ_DATA_MACD_HPP
#define FQ_DATA_MACD_HPP

#include <freequant/experiment/Indicator.h>
#include <freequant/experiment/MA.h>

namespace FreeQuant { namespace Exp {

class MACD : public Indicator {
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
    MA _ma12;
    MA _ma26;
    MA _signal;

    TimeSeries<double> _dif;
    TimeSeries<double> _dea;
    TimeSeries<double> _data;
};

}} // namespace FreeQuant


#endif // FQ_DATA_MACD_HPP
