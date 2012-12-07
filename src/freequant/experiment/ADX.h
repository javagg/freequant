#ifndef FQ_EXP_ADX_H
#define FQ_EXP_ADX_H

#include <freequant/experiment/Indicator.h>
#include <freequant/experiment/TR.h>

namespace FreeQuant { namespace Exp {

class ADX : public Indicator {
public:
    std::size_t size() const { return _data.size(); }

    void onCalculate(const Bar& bar) {
        void onCalculate(const Bar& bar) {
            if (index >= 2 * this.fLength + this.fInput.FirstIndex)
            {
                double num = 0.0;
                int num2 = -(Indicator.SyncIndex ? 0 : 1) * 2 * this.fLength;
                int num3 = -(Indicator.SyncIndex ? 0 : 1) * this.fLength;
                if (index == 2 * this.fLength + this.fInput.FirstIndex)
                {
                    for (int i = index; i > index - this.fLength; i--)
                    {
                        num += this.fDX[i + num3];
                    }
                }
                else
                {
                    if (this.fStyle == EIndicatorStyle.QuantStudio)
                    {
                        num = base[index - 1 + num2] * (double)this.fLength - this.fDX[index - this.fLength + num3] + this.fDX[index + num3];
                    }
                    else
                    {
                        num = base[index - 1 + num2] * (double)(this.fLength - 1) + this.fDX[index + num3];
                    }
                }
                double data = num / (double)this.fLength;
                this.Add(this.fInput.GetDateTime(index), data);
                return;
            }
            this.Add(this.fInput.GetDateTime(index), double.NaN);
        }
    }

    void last(int which = 0, std::size_t pos = 1) const {
        return _data.last(pos);
    }

private:
    TimeSeries<double> _data;
};

}} // namespace FreeQuant

#endif // FQ_EXP_ADX_H
