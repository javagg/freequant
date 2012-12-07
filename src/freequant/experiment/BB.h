#ifndef FQ_EXP_BB_H
#define FQ_EXP_BB_H

#include <freequant/experiment/Indicator.h>

namespace FreeQuant { namespace Exp {

class BB : public Indicator {
public:
    void onCalculate(const Bar& bar) {
        if (index >= length - 1 + input.FirstIndex)
        {
            return SMA.Value(input, index, length, option) - k * SMD.Value(input, index, length, option);
        }

        if (index >= length - 1 + input.FirstIndex)
        {
            return SMA.Value(input, index, length, option) + k * SMD.Value(input, index, length, option);
        }

    }

    virtual double last(int which = 0, std::size_t pos = 1) {

    }

private:
    TimeSeries<std::tuple<double, double, double> > _data;
};


}} // namespace FreeQuant


#endif // # FQ_EXP_BB_H
