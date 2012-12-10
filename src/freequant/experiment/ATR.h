#ifndef FQ_DATA_ATR_HPP
#define FQ_DATA_ATR_HPP

#include <freequant/experiment/Indicator.h>
#include <freequant/experiment/TR.h>

namespace FreeQuant { namespace Exp {

//True Range is the greatest of the following three values:
//    difference between the current maximum and minimum (high and low);
//    difference between the previous closing price and the current maximum;
//    difference between the previous closing price and the current minimum.
//The indicator of Average True Range is a moving average of values of the true range.
class ATR : public Indicator {
public:
    ATR(int n = 14) : _n(n) {}
    void onCalculate(const Bar& bar) {
        _tr.onCalculate(bar);
        double atr = 0;
        if (size() > 0) {
            atr = _tr.last(2)*(_n-1) + last();
        }
        append(bar.dateTime(), atr);
    }

    virtual std::size_t size() const {
        return _data.size();
    }

    double last(std::size_t pos = 1, int which = 0) {
        return _data.last(pos);
    }

    void append(const DateTime& datetime, double value, int which = 0)  {
         _data.append(datetime, value);
    }

private:
    int _n;
    TR _tr;
    TimeSeries<double> _data;
};

}} // namespace FreeQuant

#endif // FQ_DATA_ATR_HPP
