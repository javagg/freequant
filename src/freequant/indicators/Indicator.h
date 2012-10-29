#ifndef FQ_INDICATORS_INDICATOR_H
#define FQ_INDICATORS_INDICATOR_H

#include <string>

#include <freequant/marketdata/Bar.h>

namespace FreeQuant {

class Indicator {
public:
    Indicator();
    virtual ~Indicator() {}
    virtual void onBar(const FreeQuant::Bar&) = 0;
    std::string name();
};

} // namespace FreeQuant

#endif // FQ_INDICATORS_INDICATOR_H
