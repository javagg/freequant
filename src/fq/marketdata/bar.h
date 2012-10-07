#ifndef FQ_MARKETDATA_BAR_H
#define FQ_MARKETDATA_BAR_H

#include <fq/utils/datetime.h>

namespace FreeQuant { namespace MarketData {

class Bar {
public:
    Bar();
    FreeQuant::Utils::DateTime beginTime();
    FreeQuant::Utils::DateTime endTime();
    double open() { return m_open; }
    double high() { return m_high; }
    double low() { return m_low; }
    double close() { return m_close; }
    long volume() { return m_volume; }

    double median() { return (high()+low())/2; }
    double typical() { return (high()+low()+close())/3; }
    double weighted() { return (high()+low()+2*close())/4; }
private:
    double m_open;
    double m_high;
    double m_low;
    double m_close;
    long m_volume;
};

}}
#endif // FQ_MARKETDATA_BAR_H
