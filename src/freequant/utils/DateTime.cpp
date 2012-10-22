#include <boost/date_time.hpp>
#include "DateTime.h"

namespace FreeQuant {

DateTime::DateTime(const std::string& s) :
    _datetime(boost::posix_time::time_from_string(s)) {
}

}
