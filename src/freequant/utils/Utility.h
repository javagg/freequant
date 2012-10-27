#ifndef FQ_UTILS_GUID_H
#define FQ_UTILS_GUID_H

#include <map>
#include <string>

namespace FreeQuant {

std::string toGuidString();
std::string toGuidString1();
std::map<std::string, std::string> parseParamsFromString(const std::string& str);

}

#endif // FQ_UTILS_GUID_H
