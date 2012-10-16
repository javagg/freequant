#include <boost/filesystem.hpp>

#include "CsvParser.h"

namespace FreeQuant {

bool CsvParser::load(const std::string filename) {
    boost::filesystem::path path(filename);
    if (!boost::filesystem::exists(path)
        || boost::filesystem::is_directory(path)) {
        return false;
    }
}

bool CsvParser::hasMoreRows() const {
    return false;
}

} // namespace FreeQuant
