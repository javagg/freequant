#ifndef FQ_BAR_H
#define FQ_BAR_H

#include <fq/utils/datetime.h>

namespace FreeQuant {

class Bar {
public:
    Bar();
    FreeQuant::Utils::DateTime beginTime();
    FreeQuant::Utils::DateTime endTime();
    double open();
    double high();
    double low();
    double close();
    long volume();

    double median() { return (high()+low())/2; }
    double typical() { return (high()+low()+close())/3; }
    double weighted() { return (high()+low()+2*close())/4; }
};

}
#endif // FQ_BAR_H
