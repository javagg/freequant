#ifndef FQ_EXP_BB_H
#define FQ_EXP_BB_H

#include <freequant/experiment/Indicator.h>
#include <freequant/experiment/MA.h>

namespace FreeQuant { namespace Exp {

class BB : public Indicator {
public:
    BB(int n = 20, double _width = 2.0) :
        _n(n), _sd(sd), _ma(n, Bar::BarItemTypical)
    {}
    void onCalculate(const Bar& bar) {
        _ma.onCalculate(bar);
        double mid = 0;
        double upper = 0;
        double lower = 0;
        if (size() > _n) {
            mid = _ma.last();
            double sd = 0.2;
            upper = mid + sd*_width;
            lower = mid - sd*_width;
        }
        append(bar.dateTime(), make_tuple(mid, upper, lower));
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

    void append(const DateTime& datetime, const std::tuple<double, double, double>& value, int which = 0)  {
         _data.append(datetime, value);
    }

private:
    int _n;
    double _width;
    MA _ma;
    TimeSeries<std::tuple<double, double, double> > _data;
};


}} // namespace FreeQuant


#endif // # FQ_EXP_BB_H
