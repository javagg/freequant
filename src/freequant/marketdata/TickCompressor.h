#ifndef FQ_TICKCOMPRESSOR_H
#define FQ_TICKCOMPRESSOR_H

#include <freequant/utils/DateTime.h>

namespace FreeQuant {

template <typename Tick, typename Bar>
class TickCompressor {
public:
    enum BarPeriod { Second, Miniute, Hour, Day, Week, Month };
    typedef std::function<void(const std::vector<Tick>&)> AccumulateFunc;

    DateTime barBeginTime;
    DateTime barEndTime;
    long barSizeInSeconds;

    TickCompressor(const AccumulateFunc& accumu, BarPeriod period = Miniute, int k = 1) :
        accumu(accumu), period(period), k(k) {}
    void compress(const Tick& tick) {
        static bool first = true;
        if (first) {
            first = false;
            DateTime dt = tick.datetime;
            int y = dt.year();
            int m = dt.month();
            int d = dt.day();
            int h = dt.hour();
            int mm = dt.minute();
            int s = dt.second();

            switch (period) {
            case Second:
                s = static_cast<int>(std::floor(static_cast<double>(s/k+1)))*k;
                barSizeInSeconds = k;
                break;
            case Miniute:
                s = 0;
                mm = static_cast<int>(std::floor(static_cast<double>(mm/k+1)))*k;
                barSizeInSeconds = k*60;
                break;
            case Hour:
                s = 0;
                mm = 0;
                h = static_cast<int>(std::floor(static_cast<double>(h/k+1)))*k;
                barSizeInSeconds = k*60*60;
                break;
            case Day: case Week: case Month:
            default:
                break;
            }

            barBeginTime = barEndTime = DateTime(y, m, d, h, mm, s);
            barBeginTime = barBeginTime.addSeconds(-barSizeInSeconds);
        }

        if (tick.datetime > barEndTime) {
            accumu(ticksInBar);
//            onBar(bar);
            barBeginTime = barEndTime;
            barEndTime.addSeconds(barSizeInSeconds);
            ticksInBar.clear();
        }
        ticksInBar.push_back(tick);
    }

    void add(Tick& tick) {
//        if (item.Price < this.bar.Low)
//        {
//            this.bar.bar.Low = item.Price;
//        }
//        if (item.Price > this.bar.High)
//        {
//            this.bar.bar.High = item.Price;
//        }
//        this.bar.bar.Close = item.Price;
//        this.bar.bar.Volume += (long)item.Size;
    }

private:
    const AccumulateFunc& accumu;
    BarPeriod period;
    int k;
    std::vector<Tick> ticksInBar;
};

template<typename Tick, typename Bar>
struct DefaultTickAccumulation {
    Bar operator()(const std::vector<Tick>& ticks) {
        double high = 0.0;
        double low = 0.0;
        double close = 0.0;
        long volume = 0;
        for_each(ticks.begin(), ticks.end(), [&](Tick tick){
            double price = tick.price();
            if (price < low) {
                low = price;
            }
            if (price > high) {
                high = price;
            }
            close = price;
            volume += tick.volume();
        });
        return Bar();
    }
};

} // namespace FreeQuant

#endif // FQ_TICKCOMPRESSOR_H
