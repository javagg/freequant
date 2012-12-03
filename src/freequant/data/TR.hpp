#ifndef FQ_DATA_TR_H
#define FQ_DATA_TR_H

#include <tuple>
#include <vector>

#include "Indicator.h"
#include "TimeSeries.hpp"
#include "MA.h"

namespace FreeQuant { namespace Data {

template <typename DateTime, typename Bar>
class TR : public Indicator<DateTime, Bar> {
public:
    TR(int n = 14) : _ma(n) {}
//    virtual std::size_t size() {
//        return _data.size();
//    }

//    void add(const DateTime& datetime, const std::map<std::string, double>& values) {

//    }

    void onCalculate(const Bar& bar) {
        lastClose = bar.close();
        if (_data.size() < 2) {
            return;
        }
        double high = bar.high();
        double low = bar.low();
        double v1 = std::abs(high-low);
        double v2 = std::abs(high-lastClose);
        double v3 = std::abs(lastClose-low);

        double value = std::max(v1, std::max(v2, v3));
        _data.append(std::make_pair(bar.datetime(), value));
    }

//    void add(const DateTime& datetime, std::vector<double>& values) {

//    }

//    double last(const std::string& column, std::size_t pos = 1) {
//        return 0;
//    }

private:
    double lastClose;
    MA<DateTime, Bar>_ma;
    TimeSeries<DateTime, double> _data;
};

}}

#endif // FQ_DATA_TR_H
