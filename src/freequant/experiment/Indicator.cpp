#include "Indicator.h"

namespace FreeQuant { namespace Exp {

bool Indicator::contains(const FreeQuant::DateTime& datetime) {
    return false;
}

bool Indicator::contains(const FreeQuant::Bar& bar) {
    return contains(bar.endTime());
}

Indicator::Cross Indicator::cross(double level, const FreeQuant::Bar& bar) {
    return cross(level, bar.endTime());
}

Indicator::Cross Indicator::cross(double level, const FreeQuant::DateTime& datetime) {}
Indicator::Cross Indicator::cross(const Indicator& indicator, const FreeQuant::Bar& bar) {}
Indicator::Cross Indicator::cross(const TimeSeries<double>& indicator, const FreeQuant::DateTime& datetime) {}
Indicator::Cross Indicator::cross(const BarSeries& bars, const FreeQuant::DateTime& datetime) {}
Indicator::Cross Indicator::cross(const BarSeries& bars, const FreeQuant::DateTime& datetime, FreeQuant::Bar::Item item) {}

bool Indicator::crossAbove(const BarSeries& bars, FreeQuant::Bar::Item item) {
    return false;
}


}} // namespace FreeQuant
