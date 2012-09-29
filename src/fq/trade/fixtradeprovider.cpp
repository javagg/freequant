#include <quickfix/Application.h>
#include <quickfix/MessageCracker.h>
#include <quickfix/SessionFactory.h>
#include <quickfix/SessionSettings.h>
#include <quickfix/SocketInitiator.h>
#include <quickfix/FileStore.h>
#include <quickfix/FileLog.h>
#include <quickfix/fix42/NewOrderSingle.h>
#include <quickfix/fix44/Logon.h>
#include <quickfix/fix44/Logout.h>
#include <quickfix/fix44/MarketDataRequest.h>
#include <quickfix/fix44/MarketDataRequestReject.h>
#include <quickfix/fix44/MarketDataSnapshotFullRefresh.h>
#include <quickfix/fix44/MarketDataIncrementalRefresh.h>

#include "fixtradeprovider.h"

using namespace std;

namespace FreeQuant { namespace Trade {

FixTradeProvider::FixTradeProvider() {
    string config = "config.fix";
    senderCompId = "ME";
    targetCompId = "FQ";
    m_settings = new FIX::SessionSettings(config);
    m_storeFactory = new FIX::FileStoreFactory(*m_settings);
    m_initiator = new FIX::SocketInitiator(*this, *m_storeFactory, *m_settings);
}

FixTradeProvider::~FixTradeProvider() {
    delete m_initiator;
    delete m_storeFactory;
    delete m_initiator;
}

void FixTradeProvider::logon() {
    FIX44::Logon message;
    message.setField(FIX::EncryptMethod(FIX::EncryptMethod_NONE));
    message.setField(FIX::HeartBtInt(10));
    message.setField(FIX::Username("alex"));
    message.setField(FIX::Password("12345"));
    FIX::Session::sendToTarget(message, *m_sessionId);
}

void FixTradeProvider::onLogon() {

}

void FixTradeProvider::logout() {

}

void FixTradeProvider::onLogout() {

}

void FixTradeProvider::subscribe(std::vector<std::string> symbols) {
    FIX::MDReqID mdReqId("MARKETDATAID");
    FIX::SubscriptionRequestType subType(FIX::SubscriptionRequestType_SNAPSHOT);
    FIX::MarketDepth marketDepth(0);

    FIX44::MarketDataRequest::NoMDEntryTypes mdEntries;
    FIX::MDEntryType mdEntry(FIX::MDEntryType_BID);
    mdEntries.set(mdEntry);

    FIX44::MarketDataRequest::NoRelatedSym syms;
    FIX::Symbol symbol("GOOG");
    syms.set(symbol);

    FIX44::MarketDataRequest message(mdReqId, subType, marketDepth);
    message.addGroup(mdEntries);
    message.addGroup(syms);

    try {
        FIX::Session::sendToTarget(message, *m_sessionId);
    } catch (FIX::SessionNotFound&) {}
}

void FixTradeProvider::unsubscribe(std::vector<std::string> symbols) {

}

void FixTradeProvider::sendOrder() {
    string orderId = "111";
    string orderSymbol = "600446";
    char orderSide = '1';

    FIX42::NewOrderSingle newOrderSingle(FIX::ClOrdID(orderId), FIX::HandlInst(FIX::HandlInst_AUTOEXECPRIV),
                                         FIX::Symbol("600446"), FIX::Side(orderSide), FIX::TransactTime(),
                                         FIX::OrdType(FIX::OrdType_LIMIT));
//    newOrderSingle.setField(FIX::FIELD::Currency, "CNY");
//    newOrderSingle.setField(FIX::FIELD::OrderQty, "100");
//    newOrderSingle.setField(FIX::FIELD::Price, "14.44");
//    newOrderSingle.setField(FIX::FIELD::SecurityExchange, "XSHG");
//    FIX::Session::sendToTarget(newOrderSingle, sessionID);
}

void FixTradeProvider::connect() {
    cerr << "connect..." << endl;

    m_sessionId = new FIX::SessionID("FIX.4.3", senderCompId, targetCompId);
    m_initiator->start();
    logon();
}

void FixTradeProvider::disconnect() {
    if (m_sessionId != 0) {
        delete m_sessionId;
        m_sessionId = 0;
    }
    m_initiator->stop();
}

bool FixTradeProvider::isConnected() const {

}

void FixTradeProvider::onCreate(const FIX::SessionID&) {

}

void FixTradeProvider::onLogon(const FIX::SessionID&) {
    cerr << "onLogon" << endl;
}

void FixTradeProvider::onLogout(const FIX::SessionID&) {
    cerr << "onLogout" << endl;
}

void FixTradeProvider::toAdmin(FIX::Message& message, const FIX::SessionID& sessionId) {

}

void FixTradeProvider::toApp(FIX::Message&, const FIX::SessionID& sessionId) throw(FIX::DoNotSend) {
}

void FixTradeProvider::fromAdmin(const FIX::Message& message, const FIX::SessionID& sessionId)
        throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon) {
    crack(message, sessionId);
}

void FixTradeProvider::fromApp(const FIX::Message& message, const FIX::SessionID& sessionId)
        throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType) {
    crack(message, sessionId);
}

void FixTradeProvider::onMessage(const FIX44::MarketDataRequestReject& message, const FIX::SessionID &) {

}

void FixTradeProvider::onMessage(const FIX44::MarketDataIncrementalRefresh& message, const FIX::SessionID &) {
//    try
//     {
//         MDReqID mdreqid = new MDReqID();
//         NoMDEntries nomdentries = new NoMDEntries();
//         QuickFix42.MarketDataIncrementalRefresh.NoMDEntries group
//             = new QuickFix42.MarketDataIncrementalRefresh.NoMDEntries();
//         MDUpdateAction mdupdateaction = new MDUpdateAction();
//         DeleteReason deletereason = new DeleteReason();
//         MDEntryType mdentrytype = new MDEntryType();
//         MDEntryID mdentryid = new MDEntryID();
//         Symbol symbol = new Symbol();
//         MDEntryOriginator mdentryoriginator = new MDEntryOriginator();
//         MDEntryPx mdentrypx = new MDEntryPx();
//         Currency currency = new Currency();
//         MDEntrySize mdentrysize = new MDEntrySize();
//         ExpireDate expiredate = new ExpireDate();
//         ExpireTime expiretime = new ExpireTime();
//         NumberOfOrders numberoforders = new NumberOfOrders();
//         MDEntryPositionNo mdentrypositionno = new MDEntryPositionNo();

//         message.get(nomdentries);

//         message.getGroup(1, group);

//         int list = nomdentries.getValue();

//         for (uint i = 0; i < list; i++)
//         {
//             message.getGroup(i + 1, group);
//             group.get(mdupdateaction);
//             if (mdupdateaction.getValue() == '2')
//                 Console.WriteLine("Enter");
//             group.get(deletereason);
//             group.get(mdentrytype);
//             group.get(mdentryid);
//             group.get(symbol);
//             group.get(mdentryoriginator);
//             if (mdupdateaction.getValue() == '0')
//                 group.get(mdentrypx);
//             group.get(currency);
//             if (mdupdateaction.getValue() == '0')
//                 group.get(mdentrysize);
//         }

//         Console.WriteLine("Got Symbol {0} Price {1}",
//     symbol.getValue(), mdentrypx.getValue());
//     }
//     catch (Exception ex)
//     {
//         Console.WriteLine(ex.Message);
//     }
}

void FixTradeProvider::onMessage(const FIX44::MarketDataSnapshotFullRefresh& message, const FIX::SessionID &) {

//    string Symbol = message.get(new Symbol()).getValue();

//    NoMDEntries noMDEntries = new NoMDEntries();
//    message.get(noMDEntries);
//    var group =
//      new QuickFix42.MarketDataSnapshotFullRefresh.NoMDEntries();
//    MDEntryType MDEntryType = new MDEntryType();
//    MDEntryPx MDEntryPx = new MDEntryPx();
//    MDEntrySize MDEntrySize = new MDEntrySize();

//    message.getGroup(1, group);
//    group.get(MDEntryType);
//    group.get(MDEntryPx);
//    group.get(MDEntrySize);

//    message.getGroup(2, group);
//    group.get(MDEntryType);
//    group.get(MDEntryPx);
//    group.get(MDEntrySize);

//    Console.WriteLine("Symbol {0} Price {1}", Symbol, MDEntryPx);
}

}}
