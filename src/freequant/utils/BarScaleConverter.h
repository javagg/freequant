#ifndef FQ_UTILS_BARSCALECONVERTER_H
#define FQ_UTILS_BARSCALECONVERTER_H

namespace FreeQuant {

class BarScaleConverterr {
public:
    static void toSecondly();
    static void toMinutely();
    static void toHourly();
    static void toDaily();
    static void toWeekly();
    static void toMonthly();
    static void toQuarterly();
    static void toYearly();
};

}

#endif // FQ_UTILS_BARSCALECONVERTER_H
