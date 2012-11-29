#ifndef FQ_MARKETDATA_TICK_H
#define FQ_MARKETDATA_TICK_H

#include <iostream>
#include <string>

#include <freequant/utils/DateTime.h>

namespace FreeQuant {

struct Tick {
    Tick() : datetime(FreeQuant::DateTime::now()) {}

    FreeQuant::DateTime datetime;
    std::string symbol;
    std::string exchange;

    double bid;
    long bidSize;
    double ask;
    long askSize;

    double open;
    double high;
    double low;
    double close;

    // Price of the last deal (Last)
    double last;
    // Volume for the current Last price
    long volume;
    friend std::ostream& operator<<(std::ostream&, const FreeQuant::Tick&);
};

std::ostream& operator<<(std::ostream&, const FreeQuant::Tick&);

}

#endif // FQ_MARKETDATA_TICK_H
