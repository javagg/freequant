#ifndef FQ_UTILS_TIMESERIES_H
#define FQ_UTILS_TIMESERIES_H

#include <freequant/utils/DateTime.h>

namespace FreeQuant {

class TimeSeries
{
public:
    TimeSeries();
    bool contains(FreeQuant::DateTime) const;
    std::size_t size() const;
    FreeQuant::DateTime cross(TimeSeries&);
    FreeQuant::DateTime first();
    FreeQuant::DateTime last();
};

} // namespace FreeQuant

#endif // FQ_UTILS_TIMESERIES_H
