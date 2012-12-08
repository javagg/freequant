#ifndef FQ_EXP_AD_H
#define FQ_EXP_AD_H

#include <freequant/experiment/Indicator.h>
#include <freequant/experiment/TR.h>

namespace FreeQuant { namespace Exp {

class AD : public Indicator {
public:
    std::size_t size() const { return _data.size(); }

    void onCalculate(const Bar& bar) {
        double prev = size() < 1 ? 0 : last();
        double high = bar.high();
        double low = bar.low();
        double close = bar.close();
        long volume = bar.volume();
        double clv = ((close-low)-(high-close))/(high-low);
        double value = prev+clv*volume;
        append(bar.dateTime(), value);
    }

    double last(std::size_t pos = 1, int which = 0) {
        return _data.last(pos);
    }

    void append(const DateTime& datetime, double value, int which = 0) {
        _data.append(datetime, value);
    }

private:
    TimeSeries<double> _data;
};

}} // namespace FreeQuant

#endif // FQ_EXP_AD_H
