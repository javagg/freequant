#ifndef FQ_SERVER_EXECUTOR_H
#define FQ_SERVER_EXECUTOR_H

#include <memory>
#include <list>

#include <quickfix/Field.h>
#include <quickfix/Application.h>
#include <quickfix/MessageCracker.h>

#include <freequant/utils/MarketDataGenerator.h>
#include <freequant/marketdata/MarketDataProvider.h>
#include <freequant/utils/Timer.h>

namespace FIX {
    USER_DEFINE_LOCALMKTDATE(SimulationStart, 10000);
    USER_DEFINE_LOCALMKTDATE(SimulationEnd, 10001);
}

namespace FreeQuant {

class OrderBook;
/*!
 *
 * It is a market data feed simulator that utilizes the QuickFIX to
 * generate real-time feeds to clients.
 */

class Executor : public FIX::Application, public FIX::MessageCracker {
public:
    Executor();
    Executor(const std::string& filename);
    virtual ~Executor();
    void onCreate(const FIX::SessionID&);
    void onLogon(const FIX::SessionID&);
    void onLogout(const FIX::SessionID&);
    void toAdmin(FIX::Message&, const FIX::SessionID&);
    void toApp(FIX::Message&, const FIX::SessionID&) throw(FIX::DoNotSend);
    void fromAdmin(const FIX::Message&, const FIX::SessionID&)
        throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon);
    void fromApp(const FIX::Message&, const FIX::SessionID&)
        throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType);


    void onMessage(const FIX42::BusinessMessageReject&, const FIX::SessionID&) {}
    void onMessage(const FIX42::Logon&, const FIX::SessionID&) {}
    void onMessage(const FIX42::Logout&, const FIX::SessionID&) {}
    void onMessage(const FIX42::NewOrderSingle&, const FIX::SessionID&) {}
    void onMessage(const FIX42::OrderCancelRequest&, const FIX::SessionID&) {}
    void onMessage(const FIX42::OrderCancelReject&, const FIX::SessionID&) {}
    void onMessage(const FIX42::OrderCancelReplaceRequest&, const FIX::SessionID&) {}


    void onMessage(const FIX42::MarketDataRequest&, const FIX::SessionID&) {}
    void onMessage(const FIX42::MarketDataSnapshotFullRefresh&, const FIX::SessionID&) {}
    void onMessage(const FIX42::MarketDataIncrementalRefresh&, const FIX::SessionID&) {}
    void onMessage(const FIX42::OrderStatusRequest&, const FIX::SessionID&) {}
    void onMessage(const FIX42::TradingSessionStatusRequest&, const FIX::SessionID&) {}
    void onMessage(const FIX42::SecurityDefinitionRequest&, const FIX::SessionID&) {}
    void onMessage(const FIX42::ResendRequest&, const FIX::SessionID&) {}
    void onMessage(const FIX42::ExecutionReport&, const FIX::SessionID&) {}
    void onMessage(const FIX42::Reject&, const FIX::SessionID&) {}
    void onMessage(const FIX42::OrderStatusRequest&, const FIX::SessionID&) {}
    void onMessage(const FIX42::SecurityDefinitionRequest&, const FIX::SessionID&) {}
    void onMessage(const FIX42::TradingSessionStatus&, const FIX::SessionID&) {}
    void onMessage(const FIX42::TradingSessionStatusRequest&, const FIX::SessionID&) {}
    void onMessage(const FIX42::TestRequest&, const FIX::SessionID&) {}

    void onMessage(const FIX43::SecurityListRequest&, const FIX::SessionID&) {}
    void onMessage(const FIX43::DerivativeSecurityListRequest&, const FIX::SessionID&) {}


    void onMessage(const FIX44::Logon&, const FIX::SessionID&);
    void onMessage(const FIX44::NewOrderSingle&, const FIX::SessionID&);
    void onMessage(const FIX44::OrderCancelRequest&, const FIX::SessionID&);
    void onMessage(const FIX44::OrderCancelReplaceRequest&, const FIX::SessionID&);
    void onMessage(const FIX44::MarketDataRequest&, const FIX::SessionID&);
    void onMessage(const FIX44::OrderStatusRequest&, const FIX::SessionID&) {}
    void onMessage(const FIX44::SettlementInstructionRequest&, const FIX::SessionID&) {}
    void onMessage(const FIX44::TradeCaptureReportRequest&, const FIX::SessionID&) {}
    void onMessage(const FIX44::TradingSessionStatusRequest&, const FIX::SessionID&) {}
    void onMessage(const FIX44::UserRequest&, const FIX::SessionID&) {}
    void onMessage(const FIX44::SecurityDefinitionRequest&, const FIX::SessionID&);
    void onMessage(const FIX44::SecurityListRequest&, const FIX::SessionID&) {}

private:
    void generateBars();
    void sendBar(const  FIX::SessionID& sessionID, const FreeQuant::Bar& bar);

    std::map<std::string, OrderBook> _orderBooks;

    friend class MdCallback;
    class MdCallback;
    std::unique_ptr<MdCallback> _mdCallback;
    std::unique_ptr<MarketDataProvider> _mdProvider;

    boost::scoped_ptr<Timer> _timerMd;
    boost::scoped_ptr<MarketDataGenerator> _mdGenerator;
    std::set<FIX::SessionID> _sessionIDs;
    typedef MarketDataGenerator::Symbols Symbols;
    typedef std::map<FIX::SessionID, Symbols> Subscriptions;
    Subscriptions _subscriptions;

};

} // namespace FreeQuant

#endif // FQ_SERVER_EXECUTOR_H
