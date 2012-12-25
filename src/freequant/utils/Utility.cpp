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
    map<string, string> params;
    if (str.empty()) return params;

    boost::split(parts, str, boost::is_any_of(";"), boost::token_compress_on);

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

//using OpenQuant.API.Indicators;
//using SmartQuant.Data;
//using SmartQuant.FIX;
//using SmartQuant.Indicators;
//using SmartQuant.Series;
//using SmartQuant.Trading;
//using System;
//namespace OpenQuant.API
//{
//	internal class EnumConverter
//	{
//		internal static OrderSide Convert(Side side)
//		{
//			switch (side)
//			{
//			case Side.Buy:
//				return OrderSide.Buy;
//			case Side.Sell:
//				return OrderSide.Sell;
//			default:
//				throw new ArgumentException(string.Format("Side is not supported - {0}", side));
//			}
//		}
//		internal static Side Convert(OrderSide side)
//		{
//			switch (side)
//			{
//			case OrderSide.Buy:
//				return Side.Buy;
//			case OrderSide.Sell:
//				return Side.Sell;
//			default:
//				throw new ArgumentException(string.Format("Unsupported OrderSide - {0}", side));
//			}
//		}
//		internal static OrderType Convert(OrdType type)
//		{
//			switch (type)
//			{
//			case OrdType.Market:
//				return OrderType.Market;
//			case OrdType.Limit:
//				return OrderType.Limit;
//			case OrdType.Stop:
//				return OrderType.Stop;
//			case OrdType.StopLimit:
//				return OrderType.StopLimit;
//			case OrdType.MarketOnClose:
//				return OrderType.MarketOnClose;
//			default:
//				switch (type)
//				{
//				case OrdType.TrailingStop:
//					return OrderType.Trail;
//				case OrdType.TrailingStopLimit:
//					return OrderType.TrailLimit;
//				default:
//					throw new ArgumentException(string.Format("OrdType is not supported - {0}", type));
//				}
//				break;
//			}
//		}
//		internal static OrdType Convert(OrderType type)
//		{
//			switch (type)
//			{
//			case OrderType.Market:
//				return OrdType.Market;
//			case OrderType.Limit:
//				return OrdType.Limit;
//			case OrderType.Stop:
//				return OrdType.Stop;
//			case OrderType.StopLimit:
//				return OrdType.StopLimit;
//			case OrderType.Trail:
//				return OrdType.TrailingStop;
//			case OrderType.TrailLimit:
//				return OrdType.TrailingStopLimit;
//			case OrderType.MarketOnClose:
//				return OrdType.MarketOnClose;
//			default:
//				throw new ArgumentException(string.Format("Unsupported OrderType - {0}", type));
//			}
//		}
//		internal static OrderStatus Convert(OrdStatus status)
//		{
//			switch (status)
//			{
//			case OrdStatus.New:
//				return OrderStatus.New;
//			case OrdStatus.PartiallyFilled:
//				return OrderStatus.PartiallyFilled;
//			case OrdStatus.Filled:
//				return OrderStatus.Filled;
//			case OrdStatus.Cancelled:
//				return OrderStatus.Cancelled;
//			case OrdStatus.Replaced:
//				return OrderStatus.Replaced;
//			case OrdStatus.PendingCancel:
//				return OrderStatus.PendingCancel;
//			case OrdStatus.Rejected:
//				return OrderStatus.Rejected;
//			case OrdStatus.PendingNew:
//				return OrderStatus.PendingNew;
//			case OrdStatus.Expired:
//				return OrderStatus.Expired;
//			case OrdStatus.PendingReplace:
//				return OrderStatus.PendingReplace;
//			}
//			throw new NotImplementedException("OrderStatus is not supported : " + status);
//		}
//		internal static CommType Convert(CommissionType commissionType)
//		{
//			switch (commissionType)
//			{
//			case CommissionType.PerShare:
//				return CommType.PerShare;
//			case CommissionType.Percent:
//				return CommType.Percent;
//			case CommissionType.Absolute:
//				return CommType.Absolute;
//			default:
//				throw new NotImplementedException("CommissionType is not supported : " + commissionType);
//			}
//		}
//		internal static OrdStatus Convert(OrderStatus status)
//		{
//			switch (status)
//			{
//			case OrderStatus.PendingNew:
//				return OrdStatus.PendingNew;
//			case OrderStatus.New:
//				return OrdStatus.New;
//			case OrderStatus.PartiallyFilled:
//				return OrdStatus.PartiallyFilled;
//			case OrderStatus.Filled:
//				return OrdStatus.Filled;
//			case OrderStatus.PendingCancel:
//				return OrdStatus.PendingCancel;
//			case OrderStatus.Cancelled:
//				return OrdStatus.Cancelled;
//			case OrderStatus.Expired:
//				return OrdStatus.Expired;
//			case OrderStatus.PendingReplace:
//				return OrdStatus.PendingReplace;
//			case OrderStatus.Replaced:
//				return OrdStatus.Replaced;
//			case OrderStatus.Rejected:
//				return OrdStatus.Rejected;
//			default:
//				throw new NotImplementedException("OrderStatus is not supported : " + status);
//			}
//		}
//		internal static InstrumentType Convert(string instrumentType)
//		{
//			switch (instrumentType)
//			{
//			case "TBOND":
//				return InstrumentType.Bond;
//			case "CS":
//				return InstrumentType.Stock;
//			case "FUT":
//				return InstrumentType.Futures;
//			case "OPT":
//				return InstrumentType.Option;
//			case "ETF":
//				return InstrumentType.ETF;
//			case "IDX":
//				return InstrumentType.Index;
//			case "FOR":
//				return InstrumentType.FX;
//			case "FOP":
//				return InstrumentType.FutOpt;
//			case "MLEG":
//				return InstrumentType.MultiLeg;
//			}
//			throw new NotImplementedException("SecurityType is not supported : " + instrumentType);
//		}
//		internal static string Convert(InstrumentType instrumentType)
//		{
//			switch (instrumentType)
//			{
//			case InstrumentType.Stock:
//				return "CS";
//			case InstrumentType.Futures:
//				return "FUT";
//			case InstrumentType.Option:
//				return "OPT";
//			case InstrumentType.FutOpt:
//				return "FOP";
//			case InstrumentType.Bond:
//				return "TBOND";
//			case InstrumentType.Index:
//				return "IDX";
//			case InstrumentType.ETF:
//				return "ETF";
//			case InstrumentType.FX:
//				return "FOR";
//			case InstrumentType.MultiLeg:
//				return "MLEG";
//			default:
//				throw new NotImplementedException("SecurityType is not supported : " + instrumentType);
//			}
//		}
//		internal static BarType Convert(SmartQuant.Data.BarType barType)
//		{
//			switch (barType)
//			{
//			case SmartQuant.Data.BarType.Time:
//				return BarType.Time;
//			case SmartQuant.Data.BarType.Tick:
//				return BarType.Tick;
//			case SmartQuant.Data.BarType.Volume:
//				return BarType.Volume;
//			case SmartQuant.Data.BarType.Range:
//				return BarType.Range;
//			default:
//				throw new NotImplementedException("BarType is not supported : " + barType);
//			}
//		}
//		internal static SmartQuant.Data.BarType Convert(BarType barType)
//		{
//			switch (barType)
//			{
//			case BarType.Time:
//				return SmartQuant.Data.BarType.Time;
//			case BarType.Tick:
//				return SmartQuant.Data.BarType.Tick;
//			case BarType.Volume:
//				return SmartQuant.Data.BarType.Volume;
//			case BarType.Range:
//				return SmartQuant.Data.BarType.Range;
//			default:
//				throw new NotImplementedException("BarType is not supported : " + barType);
//			}
//		}
//		internal static RegressionDistanceMode Convert(RegressionDistanceMode mode)
//		{
//			switch (mode)
//			{
//			case 0:
//				return RegressionDistanceMode.Time;
//			case 1:
//				return RegressionDistanceMode.Index;
//			default:
//				throw new NotImplementedException("RegressionDistanceMode is not supported : " + mode);
//			}
//		}
//		internal static RegressionDistanceMode Convert(RegressionDistanceMode mode)
//		{
//			switch (mode)
//			{
//			case RegressionDistanceMode.Time:
//				return 0;
//			case RegressionDistanceMode.Index:
//				return 1;
//			default:
//				throw new NotImplementedException("RegressionDistanceMode is not supported : " + mode);
//			}
//		}
//		internal static SmartQuant.Data.BarData Convert(BarData barData)
//		{
//			switch (barData)
//			{
//			case BarData.Close:
//				return SmartQuant.Data.BarData.Close;
//			case BarData.Open:
//				return SmartQuant.Data.BarData.Open;
//			case BarData.High:
//				return SmartQuant.Data.BarData.High;
//			case BarData.Low:
//				return SmartQuant.Data.BarData.Low;
//			case BarData.Median:
//				return SmartQuant.Data.BarData.Median;
//			case BarData.Typical:
//				return SmartQuant.Data.BarData.Typical;
//			case BarData.Weighted:
//				return SmartQuant.Data.BarData.Weighted;
//			case BarData.Average:
//				return SmartQuant.Data.BarData.Average;
//			case BarData.Volume:
//				return SmartQuant.Data.BarData.Volume;
//			case BarData.OpenInt:
//				return SmartQuant.Data.BarData.OpenInt;
//			default:
//				throw new NotImplementedException("BarData is not supported : " + barData);
//			}
//		}
//		internal static Cross Convert(ECross cross)
//		{
//			switch (cross)
//			{
//			case ECross.Above:
//				return Cross.Above;
//			case ECross.Below:
//				return Cross.Below;
//			case ECross.None:
//				return Cross.None;
//			default:
//				throw new NotImplementedException("Cross type is not supported : " + cross);
//			}
//		}
//		internal static ECross Convert(Cross cross)
//		{
//			switch (cross)
//			{
//			case Cross.Above:
//				return ECross.Above;
//			case Cross.Below:
//				return ECross.Below;
//			case Cross.None:
//				return ECross.None;
//			default:
//				throw new NotImplementedException("Cross type is not supported : " + cross);
//			}
//		}
//		internal static StopType Convert(StopType stopType)
//		{
//			switch (stopType)
//			{
//			case StopType.Fixed:
//				return 0;
//			case StopType.Trailing:
//				return 1;
//			case StopType.Time:
//				return 2;
//			default:
//				throw new NotImplementedException("Stop type is not supported : " + stopType);
//			}
//		}
//		internal static StopType Convert(StopType stopType)
//		{
//			switch (stopType)
//			{
//			case 0:
//				return StopType.Fixed;
//			case 1:
//				return StopType.Trailing;
//			case 2:
//				return StopType.Time;
//			default:
//				throw new NotImplementedException("Stop type is not supported : " + stopType);
//			}
//		}
//		internal static StopMode Convert(StopMode stopMode)
//		{
//			switch (stopMode)
//			{
//			case StopMode.Absolute:
//				return 0;
//			case StopMode.Percent:
//				return 1;
//			default:
//				throw new NotImplementedException("Stop mode is not supported : " + stopMode);
//			}
//		}
//		internal static StopMode Convert(StopMode stopMode)
//		{
//			switch (stopMode)
//			{
//			case 0:
//				return StopMode.Absolute;
//			case 1:
//				return StopMode.Percent;
//			default:
//				throw new NotImplementedException("Stop mode is not supported : " + stopMode);
//			}
//		}
//		internal static StopStatus Convert(StopStatus stopStatus)
//		{
//			switch (stopStatus)
//			{
//			case StopStatus.Active:
//				return 0;
//			case StopStatus.Executed:
//				return 1;
//			case StopStatus.Canceled:
//				return 2;
//			default:
//				throw new NotImplementedException("Stop status is not supported : " + stopStatus);
//			}
//		}
//		internal static StopStatus Convert(StopStatus stopStatus)
//		{
//			switch (stopStatus)
//			{
//			case 0:
//				return StopStatus.Active;
//			case 1:
//				return StopStatus.Executed;
//			case 2:
//				return StopStatus.Canceled;
//			default:
//				throw new NotImplementedException("Stop status is not supported : " + stopStatus);
//			}
//		}
//		internal static PutCall Convert(PutOrCall value)
//		{
//			switch (value)
//			{
//			case PutOrCall.Put:
//				return PutCall.Put;
//			case PutOrCall.Call:
//				return PutCall.Call;
//			default:
//				throw new ArgumentException(string.Format("Unsupported put or call: {0}", value));
//			}
//		}
//		internal static PutOrCall Convert(PutCall value)
//		{
//			switch (value)
//			{
//			case PutCall.Put:
//				return PutOrCall.Put;
//			case PutCall.Call:
//				return PutOrCall.Call;
//			default:
//				throw new ArgumentException(string.Format("Unsupported PutOrCall - {0}", value));
//			}
//		}
//		internal static IndicatorStyle Convert(EIndicatorStyle indicatorStyle)
//		{
//			switch (indicatorStyle)
//			{
//			case 0:
//				return IndicatorStyle.SmartQuant;
//			case 1:
//				return IndicatorStyle.MetaStock;
//			default:
//				throw new NotImplementedException("Indicator style is not supported : " + indicatorStyle);
//			}
//		}
//		internal static EIndicatorStyle Convert(IndicatorStyle indicatorStyle)
//		{
//			switch (indicatorStyle)
//			{
//			case IndicatorStyle.SmartQuant:
//				return 0;
//			case IndicatorStyle.MetaStock:
//				return 1;
//			default:
//				throw new NotImplementedException("Indicator style is not supported : " + indicatorStyle);
//			}
//		}
//		internal static BidAsk Convert(MDSide side)
//		{
//			switch (side)
//			{
//			case MDSide.Bid:
//				return BidAsk.Bid;
//			case MDSide.Ask:
//				return BidAsk.Ask;
//			default:
//				throw new NotSupportedException(string.Format("MDSide is not supported - {0}", side));
//			}
//		}
//		internal static MDSide Convert(BidAsk side)
//		{
//			switch (side)
//			{
//			case BidAsk.Bid:
//				return MDSide.Bid;
//			case BidAsk.Ask:
//				return MDSide.Ask;
//			default:
//				throw new NotSupportedException(string.Format("BidAsk is not supported - {0}", side));
//			}
//		}
//		internal static OrderBookAction Convert(MDOperation operation)
//		{
//			switch (operation)
//			{
//			case MDOperation.Insert:
//				return OrderBookAction.Insert;
//			case MDOperation.Update:
//				return OrderBookAction.Update;
//			case MDOperation.Delete:
//				return OrderBookAction.Delete;
//			case (MDOperation)3:
//				break;
//			case MDOperation.Reset:
//				return OrderBookAction.Reset;
//			default:
//				if (operation == MDOperation.Undefined)
//				{
//					return OrderBookAction.Undefined;
//				}
//				break;
//			}
//			throw new NotSupportedException(string.Format("MDOperation is not supported - {0}", operation));
//		}
//		internal static MDOperation Convert(OrderBookAction action)
//		{
//			switch (action)
//			{
//			case OrderBookAction.Insert:
//				return MDOperation.Insert;
//			case OrderBookAction.Update:
//				return MDOperation.Update;
//			case OrderBookAction.Delete:
//				return MDOperation.Delete;
//			case OrderBookAction.Reset:
//				return MDOperation.Reset;
//			case OrderBookAction.Undefined:
//				return MDOperation.Undefined;
//			default:
//				throw new NotSupportedException(string.Format("OrderBookAction is not supported - {0}", action));
//			}
//		}
//	}
//}



}
