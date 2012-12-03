#ifndef FQ_MARKETDATA_TRADE_H
#define FQ_MARKETDATA_TRADE_H

#include <iostream>
#include <string>

#include <freequant/utils/DateTime.h>

namespace FreeQuant {

struct Trade {
    enum Side { Bull, Sell };

    std::string symbol;
    FreeQuant::DateTime dateTime;
    double price;
    double cost;
    double pnl;
    long size;
};

std::ostream& operator<<(std::ostream&, const FreeQuant::Trade&);

}


#endif // FQ_MARKETDATA_TRADE_H
