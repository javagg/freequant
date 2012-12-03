#ifndef FQ_STRATEGY_POSITION_H
#define FQ_STRATEGY_POSITION_H

#include <string>

#include <freequant/utils/DateTime.h>

namespace FreeQuant {

class Position {
public:
    enum PositionSide { PSLong, PSShort };

    enum Direction { Net, Long, Short };

    Position();

    std::string symbol;
    Direction direction;
    double volume;
    double price;
    double stopLoss;
    double takeProfit;
    double commission;
    double swap;
    double profit;
    DateTime datetime;

    double getPnL();
    double getNetPnL();
    double getUnrealizedPnL();
    double getPrice();
    double getValue();
private:
//    double
};

} // namespace FreeQuant

#endif // FQ_STRATEGY_POSITION_H
