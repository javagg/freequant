#ifndef FQ_UTILS_VARIANT_H
#define FQ_UTILS_VARIANT_H

#include <boost/any.hpp>

namespace FreeQuant {

class Variant {

private:
    boost::any _data;
};

}

#endif // FQ_UTILS_VARIANT_H

