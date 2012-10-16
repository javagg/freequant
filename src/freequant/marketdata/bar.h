#ifndef FQ_MARKETDATA_BAR_H
#define FQ_MARKETDATA_BAR_H

#include <freequant/utils/datetime.h>

namespace FreeQuant {

class Bar {
public:
    Bar(double open, double high, double low, double close);
    FreeQuant::DateTime beginTime();
    FreeQuant::DateTime endTime();
    double open() const { return m_open; }
    double high() const { return m_high; }
    double low() const { return m_low; }
    double close() const { return m_close; }
    long volume() const { return m_volume; }

    double median() const { return (high()+low())/2; }
    double typical() const { return (high()+low()+close())/3; }
    double weighted() const { return (high()+low()+2*close())/4; }
private:
    double m_open;
    double m_high;
    double m_low;
    double m_close;
    long m_volume;
};

} // namespace FreeQuant

#endif // FQ_MARKETDATA_BAR_H
