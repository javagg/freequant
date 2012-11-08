#ifndef FQ_EXP_INDICATOR_H
#define FQ_EXP_INDICATOR_H

#include <string>
#include <map>

#include <freequant/marketdata/Bar.h>
#include <freequant/utils/TimeSeries.h>

namespace FreeQuant {

typedef TimeSeries<FreeQuant::Bar> BarSeries;

namespace Exp {

class Indicator {
public:
    enum Cross { Above, Below, None };

    virtual ~Indicator() {}
    virtual std::size_t size() = 0;
    virtual bool contains(const FreeQuant::DateTime& datetime);
    virtual bool contains(const FreeQuant::Bar& bar);
    virtual Cross cross(double level, const FreeQuant::Bar& bar);
    virtual Cross cross(double level, const FreeQuant::DateTime& datetime);
    /*!
     *
     * Checks if this indicator crosses another indicator at specified bar
     *
     * \brief cross
     * \param indicator
     * \param bar
     * \return
     */
    virtual Cross cross(const Indicator& indicator, const FreeQuant::Bar& bar);
    virtual Cross cross(const TimeSeries<double>& indicator, const FreeQuant::DateTime& datetime);
    virtual Cross cross(const BarSeries& bars, const FreeQuant::DateTime& datetime);
    virtual Cross cross(const BarSeries& bars, const FreeQuant::DateTime& datetime, FreeQuant::Bar::Item item);

    virtual bool crossAbove(const BarSeries& bars, FreeQuant::Bar::Item item);
    virtual void onCalculate(const FreeQuant::Bar& bar) = 0;
    virtual void add(const FreeQuant::DateTime& datetime, const std::map<std::string, double>& values) = 0;
    virtual void add(const FreeQuant::DateTime& datetime, std::vector<double>& values) = 0;
    virtual double last(const std::string& column, long long pos = 0) = 0;
};

}} // namespace FreeQuant

#endif // FQ_EXP_INDICATOR_H
