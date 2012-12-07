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
    RSI(int n = 14) : _ma(n) {}
    ~RSI() {}
    virtual std::size_t size() {
        return _data.size();
    }

    void onCalculate(const Bar& bar) {
        double num = 0.0;
        double num2 = 0.0;
        double data = double.NaN;
        if (index >= this.fLength + this.fInput.FirstIndex)
        {
            if (this.fStyle == EIndicatorStyle.QuantStudio)
            {
                if (index == this.fLength + this.fInput.FirstIndex)
                {
                    double num3 = this.fInput[index - this.fLength, this.fOption];
                    for (int i = index - this.fLength + 1; i <= index; i++)
                    {
                        double num4 = this.fInput[i, this.fOption];
                        if (num4 > num3)
                        {
                            num += num4 - num3;
                        }
                        else
                        {
                            num2 += num3 - num4;
                        }
                        num3 = num4;
                    }
                }
                else
                {
                    num = this.fUp[index - 1] * (double)this.fLength;
                    num2 = this.fDown[index - 1] * (double)this.fLength;
                    double num4 = this.fInput[index, this.fOption];
                    double num3 = this.fInput[index - 1, this.fOption];
                    if (num4 > num3)
                    {
                        num += num4 - num3;
                    }
                    else
                    {
                        num2 += num3 - num4;
                    }
                    num4 = this.fInput[index - this.fLength, this.fOption];
                    num3 = this.fInput[index - this.fLength - 1, this.fOption];
                    if (num4 > num3)
                    {
                        num -= num4 - num3;
                    }
                    else
                    {
                        num2 -= num3 - num4;
                    }
                }
            }
            else
            {
                if (index == this.fLength + this.fInput.FirstIndex)
                {
                    double num3 = this.fInput[index - this.fLength, this.fOption];
                    for (int j = index - this.fLength + 1; j <= index; j++)
                    {
                        double num4 = this.fInput[j, this.fOption];
                        if (num4 > num3)
                        {
                            num += num4 - num3;
                        }
                        else
                        {
                            num2 += num3 - num4;
                        }
                        num3 = num4;
                    }
                }
                else
                {
                    num = this.fUp[index - 1] * (double)(this.fLength - 1);
                    num2 = this.fDown[index - 1] * (double)(this.fLength - 1);
                    double num4 = this.fInput[index, this.fOption];
                    double num3 = this.fInput[index - 1, this.fOption];
                    if (num4 > num3)
                    {
                        num += num4 - num3;
                    }
                    else
                    {
                        num2 += num3 - num4;
                    }
                }
            }
            data = 100.0 - 100.0 / (1.0 + num / num2);
            num /= (double)this.fLength;
            num2 /= (double)this.fLength;
        }
        this.Add(this.fInput.GetDateTime(index), data);
        this.fUp.Add(this.fInput.GetDateTime(index), num);
        this.fDown.Add(this.fInput.GetDateTime(index), num2);
    }

    double last(int which = 0, std::size_t pos = 1) {
        return 0;
    }

private:
    Exp::MA _ma;
    TimeSeries<std::tuple<double, double, double> > _data;
};

}}

#endif // FQ_EXP_RSI_H
