#ifndef FQ_UTILS_TIMESERIES_H
#define FQ_UTILS_TIMESERIES_H

#include <freequant/utils/DateTime.h>

namespace FreeQuant {

class TimeSeries {
public:
    TimeSeries();
    std::size_t size() const;
    FreeQuant::DateTime cross(TimeSeries&);
    const FreeQuant::DateTime& first();
    FreeQuant::DateTime last();

    const FreeQuant::DateTime& beginTime() const;
    const FreeQuant::DateTime& endTime() const;
    bool contains(const FreeQuant::DateTime&) const;
    void get(FreeQuant::DateTime&);
    void append(const std::pair<FreeQuant::DateTime, double>& value) { _data.push_back(value); }
    FreeQuant::TimeSeries& between(const FreeQuant::DateTime& from, const FreeQuant::DateTime& to);
    void remove(int start, int end, bool notify = false);
    friend bool crossesAbove(const TimeSeries&, const TimeSeries&);
private:
    std::vector<std::pair<FreeQuant::DateTime, double> > _data;
};

} // namespace FreeQuant

#endif // FQ_UTILS_TIMESERIES_H
