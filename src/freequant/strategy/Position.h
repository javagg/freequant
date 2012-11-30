#ifndef FQ_STRATEGY_POSITION_H
#define FQ_STRATEGY_POSITION_H

#include <string>

namespace FreeQuant {

class Position {
public:
    enum Direction { Net, Long, Short };

    Position();

    std::string symbol;
    Direction direction;
    double volume;
    double openPrice;
    double stopLossPrice;
    double takeProfitPrice;
    double commission;

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
