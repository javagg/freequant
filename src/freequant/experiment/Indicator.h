#ifndef FQ_EXP_INDICATOR_H
#define FQ_EXP_INDICATOR_H

#include <string>
#include <map>
#include <freequant/utils/TimeSeries.h>

namespace FreeQuant { namespace Exp {

class Indicator {
public:
    typedef double Value;

    virtual ~Indicator() {}
    virtual std::size_t size() = 0;
    virtual void add(const FreeQuant::DateTime& datetime, const std::map<std::string, double>& values) = 0;
    virtual void add(const FreeQuant::DateTime& datetime, std::vector<double>& values) = 0;
    virtual double last(const std::string& column, long long pos = 0) = 0;
};

}} // namespace FreeQuant

#endif // FQ_EXP_INDICATOR_H
