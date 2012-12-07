#ifndef FQ_EXP_RSI_H
#define FQ_EXP_RSI_H

#include <tuple>
#include <vector>

#include <freequant/utils/TimeSeries.h>
#include <freequant/experiment/Indicator.h>
#include <freequant/experiment/MA.h>

namespace FreeQuant { namespace Exp {

class RSI : public Indicator {
public:
    RSI(int n = 14) : _ma(n) {}
    ~RSI() {}
    virtual std::size_t size() {
        return _data.size();
    }

    void onCalculate(const Bar& bar) {

    }

    double last(const std::string& column, long long pos = 1) {
        return 0;
    }

private:
    Exp::MA _ma;
    TimeSeries<std::tuple<double, double, double> > _data;
};

}}

#endif // FQ_EXP_RSI_H
