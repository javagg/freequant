#ifndef FQ_INDICATORS_INDICATOR_H
#define FQ_INDICATORS_INDICATOR_H

#include <string>
#include <vector>

#include <freequant/marketdata/Bar.h>

namespace FreeQuant {

class Indicator {
public:
    virtual ~Indicator() {}
//    virtual void onBar(const FreeQuant::Bar&) = 0;
    virtual void append(double value) = 0;
    virtual std::size_t size() = 0;
//    virtual void onCalculate(const FreeQuant::Bar&) = 0;
//    std::string name();
};

} // namespace FreeQuant

#endif // FQ_INDICATORS_INDICATOR_H
