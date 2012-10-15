#ifndef FQ_STRATEGY_POSITION_H
#define FQ_STRATEGY_POSITION_H

namespace FreeQuant { namespace Strategy {

class Position {
public:
    enum Direction {
        Long,
        Short
    };

    Position();

    double getPnL();
    double getNetPnL();
    double getUnrealizedPnL();
    double getPrice();
    double getValue();
private:
//    double
};

}}

#endif // FQ_STRATEGY_POSITION_H
