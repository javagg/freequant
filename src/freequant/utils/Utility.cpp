#include <sstream>
#include <utility>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "Utility.h"

#include <freequant/strategy/Order.h>
#include <freequant/marketdata/Bar.h>
#include <freequant/marketdata/Tick.h>
#include <freequant/marketdata/Trade.h>

#include <quickfix/fix44/NewOrderSingle.h>
#include <quickfix/fix44/MarketDataSnapshotFullRefresh.h>
#include <quickfix/fix44/ExecutionReport.h>

using namespace std;

namespace FreeQuant {

string toGuidString() {
    boost::uuids::uuid u = boost::uuids::random_generator()();
    stringstream ss;
    ss << u;
    return ss.str();
}

string createGuid() {
    boost::uuids::uuid u = boost::uuids::random_generator()();
    return boost::lexical_cast<std::string>(u);
}

map<string, string> parseParamsFromString(const string& str) {
    vector<string> parts;
    boost::split(parts, str, boost::is_any_of(";"), boost::token_compress_on);
    map<string, string> params;

    struct func {
        pair<string, string> operator()(string& part) const {
            vector<string> p;
            boost::split(p, part, boost::is_any_of("="), boost::token_compress_on);
            return make_pair(p[0], p[1]);
        }
    };
    transform(parts.begin(), parts.end(), inserter(params, params.end()), func());
    return params;
}

//FreeQuant::Order orderFrom(const FIX44::NewOrderSingle& message) {
//    FreeQuant::Order order;
//    return order;
//}

//FIX44::NewOrderSingle messageFrom(const FreeQuant::Order& order) {
//    FIX44::NewOrderSingle message;
//    return message;
//}

//FreeQuant::Bar barFrom(const FIX44::MarketDataSnapshotFullRefresh&) {
//    FreeQuant::Bar bar;
//    return bar;
//}

//FIX44::MarketDataSnapshotFullRefresh messageFrom(const FreeQuant::Bar&) {
//    FIX44::MarketDataSnapshotFullRefresh message;
//    return message;
//}

//FreeQuant::Tick tickFrom(const FIX44::MarketDataSnapshotFullRefresh&) {
//    FreeQuant::Tick tick;
//    return tick;
//}

//FIX44::MarketDataSnapshotFullRefresh messageFrom(const FreeQuant::Tick&) {
//    FIX44::MarketDataSnapshotFullRefresh message;
//    return message;
//}

//FreeQuant::Trade tradeFrom(const FIX44::ExecutionReport& message) {
//    FreeQuant::Trade trade;
//    return trade;
//}

//FIX44::ExecutionReport messageFrom(const FreeQuant::Trade& trade) {
//    FIX44::ExecutionReport message;
//    return message;
//}

}
