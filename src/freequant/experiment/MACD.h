#ifndef FQ_DATA_MACD_HPP
#define FQ_DATA_MACD_HPP

#include <freequant/experiment/Indicator.h>
#include <freequant/experiment/MA.h>

namespace FreeQuant { namespace Exp {

class MACD : public Indicator {
public:
    void onCalculate(const Bar& bar) {
        if (index >= this.fInput.FirstIndex)
        {
            double num = this.fEMA1[index];
            double num2 = this.fEMA2[index];
            double data = num - num2;
            this.Add(this.fInput.GetDateTime(index), data);
            return;
        }
        this.Add(this.fInput.GetDateTime(index), double.NaN);
    }
private:
    int _short;
    int _long;
    int _N;

    int _curIdx;
    double _latestValue;
    MA<DateTime, double> _ma12;
    MA<DateTime, double> _ma26;
    MA<DateTime, double> _signal;

    TimeSeries<DateTime, double> _dif;
    TimeSeries<DateTime, double> _dea;
    TimeSeries<DateTime, double> _data;
};

}} // namespace FreeQuant


#endif // FQ_DATA_MACD_HPP
