#ifndef FQ_EXP_RSI_H
#define FQ_EXP_RSI_H

#include <tuple>
#include <vector>

#include <freequant/utils/TimeSeries.h>
#include <freequant/experiment/Indicator.h>
#include <freequant/experiment/MA.h>

namespace FreeQuant { namespace Exp {

class RSI : public Indicator {
public:
    RSI(int n = 14) : _n(n), _last_close(0), _up_avg(0), _dn_avg(0) {}
    virtual std::size_t size() {
        return _data.size();
    }

    void onCalculate(const Bar& bar) {
        double close = bar.close();
        double up = 0;
        double dn = 0;
        double rmi = 0;
        if (size() > 0) {
            if (close > _last_close) {
                up = close - _last_close;
            } else {
                dn = _last_close - close;
            }
            _up_avg = (_up_avg*(_n-1)+up)/_n;
            _dn_avg = (_dn_avg*(_n-1)+dn)/_n;
            rmi = 100*(_up_avg/(_up_avg+_dn_avg));
        }

        append(bar.dateTime(), rmi);
        _last_close = close;
    }

    double last(std::size_t pos = 1, int which = 0) {
        return _data.last(pos);
    }

    void append(const DateTime& datetime, double value, int which = 0) {
        _data.append(datetime, value);
    }


private:
    int _n;
    double _last_close;
    double _up_avg;
    double _dn_avg;
    TimeSeries<double> _data;
};

}}

#endif // FQ_EXP_RSI_H
