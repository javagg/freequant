#ifndef FQ_MARKETDATA_QUOTE_H
#define FQ_MARKETDATA_QUOTE_H

namespace FreeQuant {

class Quote
{
public:
    Quote();

    double bid() { return _bid; }
    long bidSize() { return _bidSize; }
    double ask() { return _ask; }
    long askSize() { return _askSize; }
private:
    double _bid;
    long _bidSize;
    double _ask;
    long _askSize;
};

} // namespace FreeQuant

#endif // FQ_MARKETDATA_QUOTE_H
