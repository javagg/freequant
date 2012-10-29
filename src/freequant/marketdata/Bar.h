#ifndef FQ_MARKETDATA_BAR_H
#define FQ_MARKETDATA_BAR_H

#include <freequant/utils/DateTime.h>

namespace FreeQuant {

class Bar {
public:
    Bar() {}
    Bar(double open, double high, double low, double close, long volume);
    FreeQuant::DateTime beginTime();
    FreeQuant::DateTime endTime();
    double open() const { return _open; }
    double high() const { return _high; }
    double low() const { return _low; }
    double close() const { return _close; }
    long volume() const { return _volume; }

    double median() const { return (high()+low())/2; }
    double typical() const { return (high()+low()+close())/3; }
    double weighted() const { return (high()+low()+2*close())/4; }
private:
    double _open;
    double _high;
    double _low;
    double _close;
    long _volume;
};

} // namespace FreeQuant

#endif // FQ_MARKETDATA_BAR_H
