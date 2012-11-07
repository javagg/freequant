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

    void add(const FreeQuant::DateTime& datetime, const std::map<std::string, double>& values) {

    }

    void add(const FreeQuant::DateTime& datetime, std::vector<double>& values) {

    }

    double last(const std::string& column, long long pos = 0) {

    }

private:
    MA _ma;
    FreeQuant::TimeSeries<std::tuple<double, double, double> > _data;
};

}}

#endif // FQ_EXP_RSI_H
