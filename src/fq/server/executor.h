#ifndef FQ_SERVER_EXECUTOR_H
#define FQ_SERVER_EXECUTOR_H

#include <quickfix/Application.h>
#include <quickfix/MessageCracker.h>
#include <quickfix/Values.h>
#include <quickfix/Utility.h>
#include <quickfix/Mutex.h>

//#include <quickfix/fix43/MarketDataRequest.h>
//#include <quickfix/fix43/Logon.h>
//#include <quickfix/fix43/NewOrderSingle.h>

namespace FreeQuant { namespace Server {

/*!
 *
 * It is a market data feed simulator that utilizes the QuickFIX to
 * generate real-time feeds to clients.
 */
class Executor : public FIX::Application, public FIX::MessageCracker {
public:
    Executor() {}

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
    void onMessage(const FIX44::MarketDataRequest&, const FIX::SessionID&);
};

}}

#endif // FQ_SERVER_EXECUTOR_H
