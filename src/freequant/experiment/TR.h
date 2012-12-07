#ifndef FQ_DATA_TR_H
#define FQ_DATA_TR_H

#include <tuple>
#include <vector>

#include <freequant/experiment/Indicator.h>
#include <freequant/experiment/MA.h>

namespace FreeQuant { namespace Exp {

class TR : public Indicator {
public:
    virtual std::size_t size() {
        return _data.size();
    }

    void onCalculate(const Bar& bar) {
        lastClose = bar.close();
        if (_data.size() < 2) {
            return;
        }
        double high = bar.high();
        double low = bar.low();
        double v1 = std::abs(high-low);
        double v2 = std::abs(high-lastClose);
        double v3 = std::abs(lastClose-low);

        double value = std::max(v1, std::max(v2, v3));
        _data.append(bar.dateTime(), value);
    }

    double last(int which = 0, std::size_t pos = 1) {
        return 0;
    }

private:
    double lastClose;
    TimeSeries<double> _data;
};

}}

#endif // FQ_DATA_TR_H
