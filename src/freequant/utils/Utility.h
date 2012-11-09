#ifndef FQ_UTILS_GUID_H
#define FQ_UTILS_GUID_H

#include <map>
#include <string>

namespace FIX44 {
class NewOrderSingle;
}

namespace FreeQuant {

class Order;

std::string toGuidString();
std::string createGuid();
std::map<std::string, std::string> parseParamsFromString(const std::string& str);


FreeQuant::Order orderFrom(const FIX44::NewOrderSingle&);
FIX44::NewOrderSingle messageFrom(const FreeQuant::Order&);

}

#endif // FQ_UTILS_GUID_H
