#ifndef FQ_MARKETDATA_QUOTE_H
#define FQ_MARKETDATA_QUOTE_H

namespace FreeQuant {

class Quote
{
public:
    Quote();

    double bid();
    long bidSize();
    double ask();
    long askSize();
};

} // namespace FreeQuant

#endif // FQ_MARKETDATA_QUOTE_H
