#ifndef FQ_MARKETDATA_BAR_H
#define FQ_MARKETDATA_BAR_H

#include <freequant/utils/DateTime.h>

namespace FreeQuant {

class Bar {
public:
    Bar(double open = 0, double high = 0, double low = 0, double close = 0, long volume = 0) :
        _open(open), _high(high), _low(low), _close(close), _volume(volume) {
    }

    Bar(std::string symbol, FreeQuant::DateTime dateTime, double open, double high,
        double low, double close, long volume) :
        _symbol(symbol), _dateTime(dateTime), _open(open), _high(high),
        _low(low), _close(close), _volume(volume){}
    FreeQuant::DateTime beginTime();
    FreeQuant::DateTime endTime();

    const std::string& symbol() const { return _symbol; }
    const FreeQuant::DateTime& dateTime() const { return _dateTime; }
    double open() const { return _open; }
    double high() const { return _high; }
    double low() const { return _low; }
    double close() const { return _close; }
    long volume() const { return _volume; }

    double median() const { return (high()+low())/2; }
    double typical() const { return (high()+low()+close())/3; }
    double weighted() const { return (high()+low()+2*close())/4; }

private:
    std::string _symbol;
    FreeQuant::DateTime _dateTime;
    double _open;
    double _high;
    double _low;
    double _close;
    long _volume;
};

} // namespace FreeQuant

#endif // FQ_MARKETDATA_BAR_H
