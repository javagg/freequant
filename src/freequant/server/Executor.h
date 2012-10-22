#ifndef FQ_SERVER_EXECUTOR_H
#define FQ_SERVER_EXECUTOR_H

#include <memory>
#include <list>
#include <quickfix/Application.h>
#include <quickfix/MessageCracker.h>

#include <freequant/utils/MarketDataGenerator.h>

namespace FreeQuant {

/*!
 *
 * It is a market data feed simulator that utilizes the QuickFIX to
 * generate real-time feeds to clients.
 */
class Executor : public FIX::Application, public FIX::MessageCracker {
public:
    Executor();
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

private:
    std::shared_ptr<MarketDataGenerator> _mdGenerator;
    void onGenerated(const FreeQuant::Bar&);
    FIX::SessionID _sessionID;
    std::list<FIX::SessionID> _sessionIDs;
};

} // namespace FreeQuant

#endif // FQ_SERVER_EXECUTOR_H
