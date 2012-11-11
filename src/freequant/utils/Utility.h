#ifndef FQ_UTILS_GUID_H
#define FQ_UTILS_GUID_H

#include <map>
#include <string>

namespace FIX44 {
class NewOrderSingle;
class MarketDataSnapshotFullRefresh;
class ExecutionReport;
}

namespace FreeQuant {

class Order;
class Bar;
struct Tick;
struct Trade;

std::string toGuidString();
std::string createGuid();
std::map<std::string, std::string> parseParamsFromString(const std::string& str);


FreeQuant::Order orderFrom(const FIX44::NewOrderSingle&);
FIX44::NewOrderSingle messageFrom(const FreeQuant::Order&);
FreeQuant::Bar barFrom(const FIX44::MarketDataSnapshotFullRefresh&);
FIX44::MarketDataSnapshotFullRefresh messageFrom(const FreeQuant::Bar&);
FreeQuant::Tick tickFrom(const FIX44::MarketDataSnapshotFullRefresh&);
FIX44::MarketDataSnapshotFullRefresh messageFrom(const FreeQuant::Tick&);
FreeQuant::Trade tradeFrom(const FIX44::ExecutionReport&);
FIX44::ExecutionReport messageFrom(const FreeQuant::Trade&);

}

#endif // FQ_UTILS_GUID_H
