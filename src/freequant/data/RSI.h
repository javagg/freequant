#ifndef FQ_DATA_RSI_H
#define FQ_DATA_RSI_H

#include <tuple>
#include <vector>

#include "Indicator.h"
#include "TimeSeries.hpp"
#include "MA.h"

namespace FreeQuant { namespace Data {

template <typename DateTime, typename Bar>
class RSI : public Indicator<DateTime, Bar> {
public:
    RSI(int n = 14) : _ma(n) {}
    virtual std::size_t size() {
        return _data.size();
    }

    void add(const DateTime& datetime, const std::map<std::string, double>& values) {

    }

    void onCalculate(const Bar& bar);

    void add(const DateTime& datetime, std::vector<double>& values) {

    }

    double last(const std::string& column, std::size_t pos = 1) {
        return 0;
    }

private:
    MA<DateTime, Bar>_ma;
    TimeSeries<DateTime, std::tuple<double, double, double> > _data;
};

}}

#endif // FQ_EXP_RSI_H
