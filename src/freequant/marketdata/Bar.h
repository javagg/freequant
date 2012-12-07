#ifndef FQ_MARKETDATA_BAR_H
#define FQ_MARKETDATA_BAR_H

#include <iostream>
#include <freequant/utils/DateTime.h>

namespace FreeQuant {

class Bar {
public:
    enum BarSize {
        Second = 1,
        Minute = 60,
        FiveMinute = 300,
        FifteenMinute = 900,
        ThirtyMinute = 1800,
        Hour = 3600,
        FourHour = 14400,
        Day = 86400,
        Week = 604800,
        Month = 2419200,
        Year = 29030400
    };

    enum BarItem { BarItemClose, BarItemOpen, BarItemHigh, BarItemLow, BarItemMedian, BarItemTypical, BarItemWeighted,
        BarItemVolume, BarItemOpenInterest };

    enum Price { PriceClose, PriceOpen, PriceHigh, PriceLow, PriceMedian, PriceTypical, PriceWeighted };
    enum Item { Close, Open, High, Low, Median, Typical, Weighted, Volume, OpenInterest };
    Bar(double open = 0, double high = 0, double low = 0, double close = 0, long volume = 0);
    Bar(std::string symbol, DateTime dateTime, double open, double high,
        double low, double close, long volume);
    Bar& operator=(const Bar& bar);

    const std::string& symbol() const { return _symbol; }
    const DateTime& dateTime() const { return endTime(); }
    const DateTime& beginTime() const { return _begin; }
    const DateTime& endTime() const { return _end; }

    /*!
     *  Open - the price at which the bar was opened
     */
    double open() const { return _open; }

    /*!
     *  High -the maximum that was achieved during this bar
     */
    double high() const { return _high; }

    /*!
     *  Low - the minimum that was achieved during this bar;
     */
    double low() const { return _low; }

    /*!
     *  Close - the closing price of the bar.
     */
    double close() const { return _close; }

    long volume() const { return _volume; }

    long tickVolume() { return _tickVolume; }

    double median() const { return (high()+low())/2; }
    double typical() const { return (high()+low()+close())/3; }
    double weighted() const { return (high()+low()+2*close())/4; }
    double price(Price);
//    double value(BarItem);
private:
    std::string _symbol;
    DateTime _begin;
    DateTime _end;
    double _open;
    double _high;
    double _low;
    double _close;
    long _volume;
    long _tickVolume;
};

std::ostream& operator<<(std::ostream& os, const FreeQuant::Bar& bar);



} // namespace FreeQuant

#endif // FQ_MARKETDATA_BAR_H
