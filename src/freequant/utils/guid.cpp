#include <sstream>

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "guid.h"

namespace FreeQuant {

std::string toGuidString() {
    boost::uuids::uuid u = boost::uuids::random_generator()();
    std::stringstream ss;
    ss << u;
    return ss.str();
}

std::string toGuidString1() {
    boost::uuids::uuid u = boost::uuids::random_generator()();
    return boost::lexical_cast<std::string>(u);
}

}
