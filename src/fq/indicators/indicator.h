#ifndef FQ_INDICATORS_INDICATOR_H
#define FQ_INDICATORS_INDICATOR_H

#include <string>

#include <fq/marketdata/bar.h>

namespace FreeQuant { namespace Indicators {

class Indicator {
public:
    Indicator();
    virtual ~Indicator() {}
    virtual void onBar(const FreeQuant::MarketData::Bar&) = 0;
    std::string name();
};

}}

#endif // FQ_INDICATORS_INDICATOR_H
