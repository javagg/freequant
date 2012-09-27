#ifndef FQ_SERVER_EXECUTOR_H
#define FQ_SERVER_EXECUTOR_H

#include <quickfix/Application.h>
#include <quickfix/MessageCracker.h>
#include <quickfix/Values.h>
#include <quickfix/Utility.h>
#include <quickfix/Mutex.h>

#include <quickfix/fix40/NewOrderSingle.h>
#include <quickfix/fix41/NewOrderSingle.h>
#include <quickfix/fix42/NewOrderSingle.h>
#include <quickfix/fix43/NewOrderSingle.h>
#include <quickfix/fix44/NewOrderSingle.h>
#include <quickfix/fix50/NewOrderSingle.h>

namespace FreeQuant { namespace Server {

class Executor : public FIX::Application, public FIX::MessageCracker {
public:
    Executor() : m_orderID(0), m_execID(0) {}

    void onCreate(const FIX::SessionID&);
    void onLogon(const FIX::SessionID& sessionID);
    void onLogout(const FIX::SessionID& sessionID);
    void toAdmin(FIX::Message&, const FIX::SessionID&);
    void toApp(FIX::Message&, const FIX::SessionID&) throw(FIX::DoNotSend);
    void fromAdmin(const FIX::Message&, const FIX::SessionID&)
        throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon);
    void fromApp(const FIX::Message& message, const FIX::SessionID& sessionID)
        throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType);

    void onMessage(const FIX40::NewOrderSingle&, const FIX::SessionID&);
    void onMessage(const FIX41::NewOrderSingle&, const FIX::SessionID&);
    void onMessage(const FIX42::NewOrderSingle&, const FIX::SessionID&);
    void onMessage(const FIX42::OrderCancelRequest&, const FIX::SessionID&);
    void onMessage(const FIX42::MarketDataRequest&, const FIX::SessionID&);
    void onMessage(const FIX43::NewOrderSingle&, const FIX::SessionID&);
    void onMessage(const FIX44::NewOrderSingle&, const FIX::SessionID&);
    void onMessage(const FIX50::NewOrderSingle&, const FIX::SessionID&);

    std::string genOrderID() {
        std::stringstream stream;
        stream << ++m_orderID;
        return stream.str();
    }

    std::string genExecID() {
        std::stringstream stream;
        stream << ++m_execID;
        return stream.str();
    }
private:
    int m_orderID;
    int m_execID;
};

}}

#endif // FQ_SERVER_EXECUTOR_H
