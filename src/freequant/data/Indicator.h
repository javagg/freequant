#ifndef FQ_DATA_INDICATOR_HPP
#define FQ_DATA_INDICATOR_HPP

#include <map>
#include <vector>
#include <string>

#include "TimeSeries.hpp"

namespace FreeQuant { namespace Data {

template <typename DT, typename Bar>
class Indicator {
public:
    typedef TimeSeries<DT, Bar> BarSeries;
    enum BarItem { BarClose, BarOpen, BarHigh, BarLow, BarMedian, BarTypical, BarWeighted, BarVolume };
    enum MaMethod { SMA, EMA, SMMA, LWMA, WMA };
    enum Cross { CrossAbove, CrossBelow, NoCross };

    virtual ~Indicator() {}
    virtual std::size_t size() = 0;
    virtual bool contains(const DT& datetime);
    virtual bool contains(const Bar& bar);
    Cross cross(double level, const Bar& bar, std::size_t pos) {
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
//        return NoCross;
    }

    Cross cross(double level, const DT& datetime);
    /*!
     *
     * Checks if this indicator crosses another indicator at specified bar
     *
     * \brief cross
     * \param indicator
     * \param bar
     * \return
     */
    Cross cross(const Indicator& indicator, const Bar& bar);
    Cross cross(const BarSeries& bars, const DT& datetime);
    Cross cross(const BarSeries& bars, const DT& datetime, BarItem item);
    bool crossAbove(const BarSeries& bars, BarItem item);
    bool crossBelow(const BarSeries& bars, BarItem item);
    virtual void onCalculate(const Bar& bar) = 0;
    virtual double last(const std::string& column, std::size_t pos = 1) = 0;
};

}}
#endif // FQ_DATA_INDICATOR_HPP
