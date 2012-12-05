#ifndef FQ_EXP_INDICATOR_H
#define FQ_EXP_INDICATOR_H

#include <string>
#include <map>

#include <freequant/marketdata/Bar.h>
//#include <freequant/utils/TimeSeries.h>
#include <freequant/experiment/TimeSeries.h>

namespace FreeQuant {

typedef Exp::TimeSeries<Bar> BarSeries;

namespace Exp {

class Indicator {
public:
    enum MaMethod { SMA, EMA, SMMA, LWMA };
    enum Cross { CrossAbove, CrossBelow, NoCross };

    virtual ~Indicator() {}
    virtual std::size_t size() = 0;
    virtual bool contains(const DateTime& datetime);
    virtual bool contains(const Bar& bar);
    Cross cross(double level, std::size_t pos = 1) {

//        if (pos >= 0 &&  tsize = pos + 2) {

//            double num = level - this.Ago(agoN + 1);
//            double num2 = level - this.Ago(agoN);
//            if (num < 0.0 && num2 > 0.0)
//            {
//                return CrossBelow;
//            }
//            if (num > 0.0 && num2 < 0.0)
//            {
//                return CrossAbove;
//            }
//        }
        return NoCross;
    }

    /*!
     *
     * Checks if this indicator crosses another indicator at specified bar
     *
     * \brief cross
     * \param indicator
     * \param bar
     * \return
     */
    Cross cross(const Indicator& indicator, std::size_t pos = 1);
    Cross cross(const BarSeries& bars, Bar::BarItem item, std::size_t pos = 1);
    bool crossAbove(const BarSeries& bars, Bar::BarItem item, std::size_t pos = 1);
    bool crossBelow(const BarSeries& bars, Bar::BarItem item, std::size_t pos = 1);
    virtual void onCalculate(const Bar& bar) = 0;
    virtual double last(std::size_t pos = 1) = 0;
};

}} // namespace FreeQuant

#endif // FQ_EXP_INDICATOR_H
