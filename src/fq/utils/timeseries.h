#ifndef FQ_UTILS_TIMESERIES_H
#define FQ_UTILS_TIMESERIES_H

#include <fq/utils/datetime.h>

namespace FreeQuant { namespace Utils {

class TimeSeries
{
public:
    TimeSeries();
    bool contains(FreeQuant::Utils::DateTime) const;
    std::size_t size() const;
    FreeQuant::Utils::DateTime cross(TimeSeries&);
    FreeQuant::Utils::DateTime first();
    FreeQuant::Utils::DateTime last();
};

}}
#endif // FQ_UTILS_TIMESERIES_H
