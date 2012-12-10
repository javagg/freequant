#ifndef FQ_EXP_ADX_H
#define FQ_EXP_ADX_H

#include <freequant/experiment/Indicator.h>
#include <freequant/experiment/DX.h>

namespace FreeQuant { namespace Exp {

// Average Directional Movement Index
class ADX : public Indicator {
public:
    ADX(int n = 14) : _n(n), _dx(n) {}

    std::size_t size() const { return _data.size(); }

    void onCalculate(const Bar& bar) {
        _dx.onCalculate(bar);
        double adx = 0;
        if (size() > _n) {
            double last_adx = last();
            adx = (last_adx*(_n-1) + _dx.last())/_n;
        }
        append(bar.dateTime(), adx);
    }

    double last(std::size_t pos = 1, int which = 0) {
        return _data.last(pos);
    }

    void append(const DateTime& datetime, double value, int which = 0) {
        _data.append(datetime, value);
    }

private:
    int _n;
    DX _dx;
    TimeSeries<double> _data;
};

}} // namespace FreeQuant

#endif // FQ_EXP_ADX_H
