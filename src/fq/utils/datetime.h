#ifndef FQ_UTILS_DATETIME_H
#define FQ_UTILS_DATETIME_H

#include <boost/date_time.hpp>

namespace FreeQuant { namespace Utils {

class DateTime {
public:
    DateTime();
private:
    boost::posix_time::ptime datetime;
};

}}

#endif // FQ_UTILS_DATETIME_H
