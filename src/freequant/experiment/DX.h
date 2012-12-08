#ifndef FQ_EXP_DX_H
#define FQ_EXP_DX_H

#include <vector>
#include <freequant/experiment/Indicator.h>
#include <freequant/experiment/TR.h>
#include <freequant/experiment/TimeSeries.h>

namespace FreeQuant { namespace Exp {

class DX : public Indicator {
public:
    DX(int n = 14) : _n(n) {
        _dmp_sum = 0.;
        _dmm_sum = 0;
        _tr_sum = 0;
        _last_high = 0;
        _last_low = 0;
    }

    std::size_t size() const {
        return _data.size();
    }

    void onCalculate(const Bar& bar) {
        double dx = std::numeric_limits<double>::min();
        _tr.onCalculate(bar);
        double high = bar.high();
        double low = bar.low();
        if (size() > 0) {
            double dh = _last_high - high;
            double dl = _last_low - low;
            double dmp = 0;
            double dmm = 0;
            if ((dh < 0 && dl < 0) || (dl = dl)) {}
            if (dh > dl) { dmp = dh; dmm = 0; }
            if (dh < dl) { dmp = 0; dmm = dl; }
            _dmp_sum = _dmp_sum - _dmp_sum/_n + dmp;
            _dmm_sum = _dmm_sum - _dmp_sum/_n + dmm;
            _tr_sum = _tr_sum - _tr_sum/_n + _tr.last();
            double dip = _dmp_sum/_tr_sum * 100;
            double dim = _dmm_sum/_tr_sum * 100;
            dx = (dip-dim)/(dip+dim);
        }

        append(bar.dateTime(), dx);
        _last_high = high;
        _last_low = low;
    }

    double last(std::size_t pos = 1, int which = 0) {
        return _data.last(pos);
    }

    void append(const DateTime& datetime, double value, int which = 0) {
        _data.append(datetime, value);
    }

private:
    int _n;
    double _dmp_sum;
    double _dmm_sum;
    double _tr_sum;
    double _last_high;
    double _last_low;
    TimeSeries<double> _data;
    TR _tr;
};

}} // namespace FreeQuant

#endif // FQ_EXP_DX_H
