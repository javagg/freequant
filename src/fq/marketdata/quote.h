#ifndef FQ_MARKETDATA_QUOTE_H
#define FQ_MARKETDATA_QUOTE_H

namespace FreeQuant { namespace MarketData {

class Quote
{
public:
    Quote();

    double bid();
    long bidSize();
    double ask();
    long askSize();
};

}}

#endif // FQ_MARKETDATA_QUOTE_H
