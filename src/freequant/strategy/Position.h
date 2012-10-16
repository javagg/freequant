#ifndef FQ_STRATEGY_POSITION_H
#define FQ_STRATEGY_POSITION_H

namespace FreeQuant {

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

} // namespace FreeQuant

#endif // FQ_STRATEGY_POSITION_H
