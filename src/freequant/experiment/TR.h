#ifndef FQ_DATA_TR_H
#define FQ_DATA_TR_H

#include <limits>
#include <tuple>
#include <vector>

#include <freequant/experiment/Indicator.h>
#include <freequant/experiment/MA.h>

namespace FreeQuant { namespace Exp {

class TR : public Indicator {
public:
    void onCalculate(const Bar& bar) {
        double value = std::numeric_limits<double>::min();
        if (size() > 0) {
            double high = bar.high();
            double low = bar.low();
            double v1 = std::abs(high-low);
            double v2 = std::abs(high-lastClose);
            double v3 = std::abs(lastClose-low);
            double value = std::max(v1, std::max(v2, v3));
        }
        append(bar.dateTime(), value);
        lastClose = bar.close();
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
    double lastClose;
    TimeSeries<double> _data;
};

}}

#endif // FQ_DATA_TR_H
