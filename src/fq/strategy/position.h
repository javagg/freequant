#ifndef FQ_STRATEGY_POSITION_H
#define FQ_STRATEGY_POSITION_H

namespace FreeQuant { namespace Strategy {

class Position {
public:
    Position();

    double getPnL();
    double getNetPnL();
    double getUnrealizedPnL();
    double getPrice();
    double getValue();
};

}}

#endif // FQ_STRATEGY_POSITION_H
