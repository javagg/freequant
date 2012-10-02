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
    delete m_settings;
}

void FixTradeProvider::logon() {
    FIX44::Logon message;
    message.set(FIX::EncryptMethod(FIX::EncryptMethod_NONE));
    message.set(FIX::HeartBtInt(10));
    message.set(FIX::Username("alex"));
    message.set(FIX::Password("12345"));

//    cout << "message: " << message.toXML() << endl;

    try {
        FIX::Session::sendToTarget(message, *m_sessionId);
    } catch (FIX::SessionNotFound&) {}
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

    FIX44::MarketDataRequest::NoMDEntryTypes mdEntrieTypes;
    mdEntrieTypes.set(FIX::MDEntryType(FIX::MDEntryType_OPENING));
    mdEntrieTypes.set(FIX::MDEntryType(FIX::MDEntryType_CLOSING));
    mdEntrieTypes.set(FIX::MDEntryType(FIX::MDEntryType_TRADING_SESSION_HIGH_PRICE));
    mdEntrieTypes.set(FIX::MDEntryType(FIX::MDEntryType_TRADING_SESSION_LOW_PRICE));
    mdEntrieTypes.set(FIX::MDEntryType(FIX::MDEntryType_BID));
    mdEntrieTypes.set(FIX::MDEntryType(FIX::MDEntryType_OFFER));
    mdEntrieTypes.set(FIX::MDEntryType(FIX::MDEntryType_TRADE_VOLUME));
    mdEntrieTypes.set(FIX::MDEntryType(FIX::MDEntryType_OPEN_INTEREST));

    FIX44::MarketDataRequest::NoRelatedSym syms;
    syms.set(FIX::Symbol("GOOG"));
    syms.set(FIX::Symbol("GOOG"));
    syms.set(FIX::Symbol("IF1210"));

    FIX44::MarketDataRequest message(mdReqId, subType, marketDepth);
    message.set(FIX::MDUpdateType(FIX::MDUpdateType_FULL_REFRESH));
    message.set(FIX::AggregatedBook(true));
    string s;
    s.append(1, FIX::Scope_LOCAL);

    FIX::Scope scope(s);
    message.set(scope);
    message.set(FIX::MDImplicitDelete(false));
    message.addGroup(mdEntrieTypes);
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
    m_sessionId = new FIX::SessionID("FIX.4.4", senderCompId, targetCompId);
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

void FixTradeProvider::toApp(FIX::Message& message, const FIX::SessionID& sessionId) throw(FIX::DoNotSend) {
    try {
      FIX::PossDupFlag possDupFlag;
      message.getHeader().getField(possDupFlag);
      if (possDupFlag) throw FIX::DoNotSend();
    }
    catch (FIX::FieldNotFound&) {}
}

void FixTradeProvider::fromAdmin(const FIX::Message& message, const FIX::SessionID& sessionId)
        throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon) {
    crack(message, sessionId);
}

void FixTradeProvider::fromApp(const FIX::Message& message, const FIX::SessionID& sessionId)
        throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType) {
    crack(message, sessionId);
}

void FixTradeProvider::onMessage(const FIX44::MarketDataRequestReject& message, const FIX::SessionID& sessionID) {

}

struct SECURITY
{
    std::string Symbol;
    std::string MDEntryID;
    char MDUpdateAction;
    char MDEntryType;
    double MDEntryPx;
    double MDEntrySize;
    double MinQty;
    double MinInc;
    double MinBR;
    double YTM;
    double YTW;
    SECURITY(){
        MDEntryPx=0;
        MDEntrySize=0;
        MinQty=0;
        MinInc=0;
        MinBR=0;
        YTM=0;
        YTW=0;
    };
    bool operator < (const SECURITY& sec) const {
        if (Symbol < sec.Symbol)
            return true;
        else if (Symbol == sec.Symbol)
            if (MDEntryType < sec.MDEntryType)
                return true;
            else if (MDEntryType == sec.MDEntryType)
                if (MDEntryPx < sec.MDEntryPx)
                    return true;
        return false;
    }
};

void FixTradeProvider::onMessage(const FIX44::MarketDataIncrementalRefresh& message, const FIX::SessionID& sessionID) {
    FIX::NoMDEntries noMDEntries;
    message.get(noMDEntries);
    if (noMDEntries.getValue() < 1) {
        return;
    }
    if (noMDEntries.getValue() != 1) {
        std::cout << "NoMDEntries in MarketDataIncrementalRefresh is not 1!" <<std::endl;
        return;
    }
    FIX44::MarketDataIncrementalRefresh::NoMDEntries group;
    message.getGroup(1, group);

    FIX::MDEntryID entryID; group.get(entryID);
    FIX::MDUpdateAction action; group.get(action);

    char actionvalue = action.getValue();//0=New, 1=Update, 2=Delete)
//    if (actionvalue == FIX::MDUpdateAction_DELETE) {
//        std::map<std::string, SECURITY>::iterator it = securities_.end();
//        it=securities_.find(entryID);
//        if (it!=securities_.end())
//            securities_.erase(it);
//        return;
//    }

//    SECURITY security;
//    security.MDEntryID = entryID;
//    security.MDUpdateAction = action;
//    FIX::Symbol symbol;
//    if (group.isSet(symbol)){
//        group.get(symbol);
//        security.Symbol = symbol;
//    }
//    FIX::MDEntryType entryType;
//    if(group.isSet(entryType)) {
//        group.get(entryType);
//        security.MDEntryType = entryType;
//    }
//    FIX::MDEntryPx price;
//    if(group.isSet(price)) {
//        group.get(price);
//        security.MDEntryPx = price.getValue();
//    }
//    FIX::MDEntrySize size;
//    if(group.isSet(size)) {
//        group.get(size);
//        security.MDEntrySize = size.getValue();
//    }
//    FIX::MinQty qty;
//    if(group.isSet(qty)) {
//        group.get(qty);
//        security.MinQty = qty.getValue();
//    }
//    FIX::MinInc inc;
//    if(message.isSetField(inc)) {
//        message.getField(inc);
//        security.MinInc	= inc.getValue();
//    }
//    FIX::MinBR br;
//    if(message.isSetField(br)) {
//        message.getField(br);
//        security.MinBR			= br.getValue();
//    }
//    FIX::YTM ytm;
//    if(message.isSetField(ytm)) {
//        message.getField(ytm);
//        security.YTM			= ytm.getValue();
//    }
//    FIX::YTW ytw;
//    if(message.isSetField(ytw)) {
//        message.getField(ytw);
//        security.YTW			= ytw.getValue();
//    }
//    securities_[entryID] = security;
    std::cout << message.toXML() << std::endl;
}

void FixTradeProvider::onMessage(const FIX44::MarketDataSnapshotFullRefresh& message, const FIX::SessionID &) {
    std::cout << "FixTradeProvider::onMessage(const FIX44::MarketDataSnapshotFullRefresh" << std::endl;

    FIX::NoMDEntries entries;
    message.get(entries);
    std::cout << entries.getValue() << endl;

    FIX44::MarketDataSnapshotFullRefresh::NoMDEntries group;

    for (int i = 1; i <= entries; i++) {
        message.getGroup(i, group);
        FIX::MDEntrySize mdEntrySize;
        FIX::MDEntryDate mdEntryDate;
        FIX::MDEntryTime mdEntryTime;
        FIX::MDEntryType mdEntryType;
        FIX::MDEntryPx mdEntryPx;
        group.get(mdEntrySize);
        group.get(mdEntryType);
        group.get(mdEntryPx);

        switch (mdEntryType) {
        case FIX::MDEntryType_BID:
            cout << "bid" << mdEntryPx << " size:" << mdEntrySize << endl;
            break;
        case FIX::MDEntryType_OFFER:
            cout << "offer" << mdEntryPx << " size:" << mdEntrySize << endl;
            break;
        default:
            break;
        }
    }
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
