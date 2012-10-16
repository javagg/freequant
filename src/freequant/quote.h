#ifndef FQ_QUOTE_H
#define FQ_QUOTE_H

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

}
#endif // FQ_QUOTE_H
