#ifndef FQ_MARKETDATA_QUOTE_H
#define FQ_MARKETDATA_QUOTE_H

#include <iostream>
#include <string>
#include <freequant/utils/DateTime.h>

namespace FreeQuant {

class Quote
{
public:
    Quote();
    std::string& symbol() const;
    FreeQuant::DateTime dateTime;
    double bid() const { return _bid; }
    long bidSize() const { return _bidSize; }
    double ask() const { return _ask; }
    long askSize() const { return _askSize; }
private:
    double _bid;
    long _bidSize;
    double _ask;
    long _askSize;
};

} // namespace FreeQuant

#endif // FQ_MARKETDATA_QUOTE_H
