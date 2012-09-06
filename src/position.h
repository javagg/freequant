#ifndef POSITION_H
#define POSITION_H

namespace FreeQuant {

class Position {
public:
    Position();

    double getPnL();
    double getNetPnL();
    double getUnrealizedPnL();
    double getPrice();
    double getValue();
};

}
#endif // POSITION_H
