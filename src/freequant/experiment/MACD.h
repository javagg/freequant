#ifndef FQ_DATA_MACD_HPP
#define FQ_DATA_MACD_HPP

#include <freequant/experiment/Indicator.h>
#include <freequant/experiment/MA.h>

namespace FreeQuant { namespace Exp {

class MACD : public Indicator {
public:
    MACD(int fast = 12, int slow = 26, int sig = 9, MaMethod method = SMA) {}

    std::size_t size() const {
       return _data.size();
    }

    virtual void onCalculate(const Bar& bar) {
        _ma_fast.onCalculate(bar);
        _ma_slow.onCalculate(bar);

        double macd = 0;
        if (size() > _slow) {
            macd = _ma_slow.last() - _ma_fast.last();
        }

        append(bar.dateTime(), macd);
    }

    double last(std::size_t pos = 1, int which = 0) const {
        return _data.last(pos);
    }

    void append(const DateTime& datetime, double value, int which = 0) {
        _data.append(datetime, value);
    }


private:
    int _fast;
    int _slow;
    int _sig;

    MA _ma_fast;
    MA _ma_slow;
    MA _ma_sig;

    TimeSeries<double> _data;
};

}} // namespace FreeQuant


#endif // FQ_DATA_MACD_HPP
