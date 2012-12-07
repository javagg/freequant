#ifndef FQ_DATA_ATR_HPP
#define FQ_DATA_ATR_HPP

#include <freequant/experiment/Indicator.h>
#include <freequant/experiment/TR.h>

namespace FreeQuant { namespace Exp {

class ATR : public Indicator {
public:
    void onCalculate(const Bar& bar) {
//        if (index >= this.fLength + this.fInput.FirstIndex)
//        {
//            int num = -(Indicator.SyncIndex ? 0 : 1) * this.fLength;
//            double data;
//            if (this.fStyle == EIndicatorStyle.QuantStudio)
//            {
//                if (index == this.fLength + this.fInput.FirstIndex)
//                {
//                    double num2 = 0.0;
//                    for (int i = index; i > index - this.fLength; i--)
//                    {
//                        num2 += TR.Value(this.fInput, i);
//                    }
//                    data = num2 / (double)this.fLength;
//                }
//                else
//                {
//                    double num3 = TR.Value(this.fInput, index);
//                    data = (base[index - 1 + num] * (double)this.fLength + num3 - TR.Value(this.fInput, index - this.fLength)) / (double)this.fLength;
//                }
//            }
//            else
//            {
//                if (index == this.fLength + this.fInput.FirstIndex)
//                {
//                    double num4 = 0.0;
//                    for (int j = index; j > index - this.fLength; j--)
//                    {
//                        num4 += TR.Value(this.fInput, j);
//                    }
//                    data = num4 / (double)this.fLength;
//                }
//                else
//                {
//                    double num3 = TR.Value(this.fInput, index);
//                    data = (base[this.fInput.GetDateTime(index - 1)] * (double)this.fLength + num3 - TR.Value(this.fInput, index - this.fLength)) / (double)this.fLength;
//                }
//            }
//            this.Add(this.fInput.GetDateTime(index), data);
//            return;
//        }
//        this.Add(this.fInput.GetDateTime(index), double.NaN);
    }
private:
    const static int ma_len = 14;
    TR _tr;
    TimeSeries<double> _data;
};

}} // namespace FreeQuant

#endif // FQ_DATA_ATR_HPP
