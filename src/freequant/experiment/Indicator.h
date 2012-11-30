#ifndef FQ_EXP_INDICATOR_H
#define FQ_EXP_INDICATOR_H

#include <string>
#include <map>

#include <freequant/marketdata/Bar.h>
#include <freequant/utils/TimeSeries.h>

namespace FreeQuant {

typedef TimeSeries<Bar> BarSeries;

namespace Exp {

class Indicator {
public:
    enum Item { PriceClose, PriceOpen, PriceHigh, PriceLow, PriceMedian, PriceTypical, PriceWeighted,
        VolumeTrade, VolumeReal = VolumeTrade, VolumeTick, VolumeOpenInterest };

    enum MaMethod { SMA, EMA, SMMA, LWMA };
    enum Cross { Above, Below, NoCross };

    virtual ~Indicator() {}
    virtual std::size_t size() = 0;
    virtual bool contains(const DateTime& datetime);
    virtual bool contains(const Bar& bar);
    virtual Cross cross(double level, const Bar& bar);
    virtual Cross cross(double level, const DateTime& datetime);
    /*!
     *
     * Checks if this indicator crosses another indicator at specified bar
     *
     * \brief cross
     * \param indicator
     * \param bar
     * \return
     */
    virtual Cross cross(const Indicator& indicator, const Bar& bar);
    virtual Cross cross(const TimeSeries<double>& indicator, const DateTime& datetime);
    virtual Cross cross(const BarSeries& bars, const DateTime& datetime);
    virtual Cross cross(const BarSeries& bars, const DateTime& datetime, Bar::Item item);

    virtual bool crossAbove(const BarSeries& bars, Bar::Item item);
    virtual void onCalculate(const Bar& bar) = 0;
    virtual void add(const DateTime& datetime, const std::map<std::string, double>& values) = 0;
    virtual void add(const DateTime& datetime, std::vector<double>& values) = 0;
    virtual double last(const std::string& column, long long pos = 0) = 0;
};

}} // namespace FreeQuant

#endif // FQ_EXP_INDICATOR_H
