#ifndef FQ_EXP_MA_H
#define FQ_EXP_MA_H

#include <freequant/experiment/Indicator.h>

namespace FreeQuant { namespace Exp {

class MA : public Indicator {
public:
    MA(int window = 10) : _window(window) {}
    ~MA() {}
    virtual std::size_t size() {
        return _data.size();
    }

    void add(const FreeQuant::DateTime& datetime, const std::map<std::string, double>& values) {
//        _data.append(datetiem, values);
    }

    void add(const FreeQuant::DateTime& datetime, std::vector<double>& values) {
        if (!values.empty()) {
            double calculated = values[0];
            _data.append(datetime, calculated);
        }
    }

    double last(const std::string& column, long long pos = 0) {
        return _data.last();
    }

private:
    FreeQuant::TimeSeries<double> _data;
    int _window;
};

}} // namespace FreeQuant

#endif // FQ_EXP_MA_H
