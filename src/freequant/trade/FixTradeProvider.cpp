#include <quickfix/Application.h>
#include <quickfix/Exceptions.h>
#include <quickfix/FileStore.h>
#include <quickfix/FileLog.h>
#include <quickfix/Message.h>
#include <quickfix/MessageCracker.h>
#include <quickfix/MessageCracker.h>
#include <quickfix/SessionFactory.h>
#include <quickfix/SessionSettings.h>
#include <quickfix/SocketInitiator.h>
#include <quickfix/SessionID.h>

#include <quickfix/fix42/NewOrderSingle.h>
#include <quickfix/fix44/ExecutionReport.h>
#include <quickfix/fix44/Logon.h>
#include <quickfix/fix44/Logout.h>
#include <quickfix/fix44/ExecutionReport.h>
#include <quickfix/fix44/NewOrderSingle.h>
#include <quickfix/fix44/OrderCancelRequest.h>
#include <quickfix/fix44/OrderCancelReplaceRequest.h>
#include <quickfix/fix44/OrderCancelReject.h>
#include <quickfix/fix44/OrderCancelReject.h>
#include <quickfix/fix44/OrderStatusRequest.h>
#include <quickfix/fix44/MarketDataRequest.h>
#include <quickfix/fix44/MarketDataRequestReject.h>
#include <quickfix/fix44/MarketDataSnapshotFullRefresh.h>
#include <quickfix/fix44/MarketDataIncrementalRefresh.h>
#include <quickfix/fix44/SecurityDefinition.h>
#include <quickfix/fix44/SecurityDefinitionRequest.h>
#include <quickfix/fix44/SecurityList.h>
#include <quickfix/fix44/SecurityListRequest.h>
#include <quickfix/fix44/SecurityTypes.h>
#include <quickfix/fix44/SecurityTypeRequest.h>
#include <quickfix/fix44/NewOrderSingle.h>
#include <quickfix/fix44/OrderCancelRequest.h>

#include "FixTradeProvider.h"
#include <freequant/utils/Utility.h>
#include <freequant/strategy/Instrument.h>

using namespace std;

namespace FreeQuant {

class FixTradeProvider::Impl : private FIX::Application, private FIX::MessageCracker {
public:
    Impl(std::string filename, TradeProvider::Callback *callback = 0) :
        _settings(filename), _storeFactory(_settings), _initiator(*this, _storeFactory, _settings) {
    }

    Impl(std::istream& istream, TradeProvider::Callback *callback = 0) :
        _settings(istream), _storeFactory(_settings), _initiator(*this, _storeFactory, _settings) {
    }

    virtual ~Impl() {

    }

    void logon() {
        FIX44::Logon message;
        message.set(FIX::EncryptMethod(FIX::EncryptMethod_NONE));
        message.set(FIX::HeartBtInt(10));
        message.set(FIX::Username("alex"));
        message.set(FIX::Password("12345"));

        try {
            FIX::Session::sendToTarget(message);
        } catch (FIX::SessionNotFound&) {}
    }

    void logout() {

    }

    void subscribe(std::vector<std::string> symbols) {
        std::string uuid = FreeQuant::toGuidString();
        FIX::MDReqID mdReqId(uuid);
        FIX::SubscriptionRequestType subType(FIX::SubscriptionRequestType_SNAPSHOT_PLUS_UPDATES);
        FIX::MarketDepth marketDepth(1);

        FIX44::MarketDataRequest message(mdReqId, subType, marketDepth);

        message.set(FIX::MDUpdateType(FIX::MDUpdateType_INCREMENTAL_REFRESH));
        message.set(FIX::AggregatedBook(true));
        string s;
        s.append(1, FIX::Scope_LOCAL);

        FIX::Scope scope(s);
        message.set(scope);

        message.set(FIX::MDImplicitDelete(false));

        FIX44::MarketDataRequest::NoMDEntryTypes typeGroup;
        typeGroup.set(FIX::MDEntryType(FIX::MDEntryType_OPENING_PRICE));
        message.addGroup(typeGroup);
        typeGroup.set(FIX::MDEntryType(FIX::MDEntryType_CLOSING_PRICE));
        message.addGroup(typeGroup);
        typeGroup.set(FIX::MDEntryType(FIX::MDEntryType_TRADING_SESSION_HIGH_PRICE));
        message.addGroup(typeGroup);
        typeGroup.set(FIX::MDEntryType(FIX::MDEntryType_TRADING_SESSION_LOW_PRICE));
        message.addGroup(typeGroup);
        typeGroup.set(FIX::MDEntryType(FIX::MDEntryType_BID));
        message.addGroup(typeGroup);
        typeGroup.set(FIX::MDEntryType(FIX::MDEntryType_OFFER));
        message.addGroup(typeGroup);
        typeGroup.set(FIX::MDEntryType(FIX::MDEntryType_TRADE_VOLUME));
        message.addGroup(typeGroup);
        typeGroup.set(FIX::MDEntryType(FIX::MDEntryType_OPEN_INTEREST));
        message.addGroup(typeGroup);

        FIX44::MarketDataRequest::NoRelatedSym symGroup;
        symGroup.set(FIX::Symbol("GOOG"));
        message.addGroup(symGroup);
        symGroup.set(FIX::Symbol("IF1210"));
        message.addGroup(symGroup);

        try {
            FIX::Session::sendToTarget(message);
        } catch (FIX::SessionNotFound&) {}
    }

    void unsubscribe(std::vector<std::string> symbols) {
        std::string uuid = FreeQuant::toGuidString();
        FIX::MDReqID mdReqId(uuid);
        FIX::SubscriptionRequestType subType(FIX::SubscriptionRequestType_DISABLE_PREVIOUS_SNAPSHOT_PLUS_UPDATE_REQUEST);
        FIX::MarketDepth marketDepth(1);

        FIX44::MarketDataRequest message(mdReqId, subType, marketDepth);

        message.set(FIX::MDUpdateType(FIX::MDUpdateType_INCREMENTAL_REFRESH));
        message.set(FIX::AggregatedBook(true));
        string s;
        s.append(1, FIX::Scope_LOCAL);

        FIX::Scope scope(s);
        message.set(scope);

        message.set(FIX::MDImplicitDelete(false));

        FIX44::MarketDataRequest::NoMDEntryTypes typeGroup;
        typeGroup.set(FIX::MDEntryType(FIX::MDEntryType_OPENING_PRICE));
        message.addGroup(typeGroup);
        typeGroup.set(FIX::MDEntryType(FIX::MDEntryType_CLOSING_PRICE));
        message.addGroup(typeGroup);
        typeGroup.set(FIX::MDEntryType(FIX::MDEntryType_TRADING_SESSION_HIGH_PRICE));
        message.addGroup(typeGroup);
        typeGroup.set(FIX::MDEntryType(FIX::MDEntryType_TRADING_SESSION_LOW_PRICE));
        message.addGroup(typeGroup);
        typeGroup.set(FIX::MDEntryType(FIX::MDEntryType_BID));
        message.addGroup(typeGroup);
        typeGroup.set(FIX::MDEntryType(FIX::MDEntryType_OFFER));
        message.addGroup(typeGroup);
        typeGroup.set(FIX::MDEntryType(FIX::MDEntryType_TRADE_VOLUME));
        message.addGroup(typeGroup);
        typeGroup.set(FIX::MDEntryType(FIX::MDEntryType_OPEN_INTEREST));
        message.addGroup(typeGroup);

        FIX44::MarketDataRequest::NoRelatedSym symGroup;
        symGroup.set(FIX::Symbol("GOOG"));
        message.addGroup(symGroup);
        symGroup.set(FIX::Symbol("IF1210"));
        message.addGroup(symGroup);

        try {
            FIX::Session::sendToTarget(message);
        } catch (FIX::SessionNotFound&) {}

    }

    void connect() {
        cerr << "connect..." << endl;
        _initiator.start();
        logon();

    //    FIX::Session *session = FIX::Session::lookupSession(*m_sessionId);
    //    if (session && !session->isLoggedOn()) {
    //        session->logon();
    //    }
    }

    void disconnect() {
    //    if (m_sessionId != 0) {
    //        delete m_sessionId;
    //        m_sessionId = 0;
    //    }
        _initiator.stop();

    //    FIX::Session *session = FIX::Session::lookupSession(*m_sessionId);
    //    if (session && session->isLoggedOn()) {
    //        session->logout();
    //    }
    }

    bool isConnected() const {
        return false;
    }

    void cancelOrder(FreeQuant::Order& o) {
        FIX44::OrderCancelRequest message;
        FIX::OrigClOrdID origClOrdID;
        FIX::ClOrdID clOrdID;
        message.set(origClOrdID);
        message.set(clOrdID);
    }

    void replaceOrder(FreeQuant::Order& o) {
        FIX44::OrderCancelReplaceRequest message;

        FIX::Session::sendToTarget(message);
    }

    void sendOrder(FreeQuant::Order& order) {
        std::string clOrdID = FreeQuant::toGuidString();

        FIX44::NewOrderSingle message;
        message.set(FIX::ClOrdID(clOrdID));
        message.set(FIX::Side(FIX::Side_SELL));
        FIX::UtcTimeStamp timestamp(2001,2,2,12,22,22,0);
        message.set(FIX::TransactTime(timestamp));
        message.set(FIX::HandlInst(FIX::HandlInst_AUTOMATED_EXECUTION_ORDER_PUBLIC_BROKER_INTERVENTION_OK));
        message.set(FIX::OrdType(FIX::OrdType_MARKET));
        message.set(FIX::Symbol("GOOG"));
        message.set(FIX::OrderQty(1));

    //    if (order.Instrument.AltSource == TTFIX.PROVIDER_NAME)
    //    {
    //        message.set(new Symbol(order.Instrument.AltSymbol));
    //        message.set(new SecurityExchange(order.Instrument.AltExchange));
    //    }
    //    else
    //    {
    //        message.set(new Symbol(order.Instrument.Symbol));
    //        message.set(new SecurityExchange(order.Instrument.Exchange));
    //    }

    //    switch (order.Side)
    //    {
    //        case OrderSide.Buy:
    //            message.set(new Side(Side.BUY));
    //            break;
    //        case OrderSide.Sell:
    //            message.set(new Side(Side.SELL));
    //            break;
    //    }

    //    message.set(new TransactTime(order.DateTime));

    //    switch (order.Type)
    //    {
    //        case OrderType.Market:
    //            {
    //                message.set(new OrdType(OrdType.MARKET));
    //            }
    //            break;
    //        case OrderType.Limit:
    //            {
    //                message.set(new OrdType(OrdType.LIMIT));
    //                message.set(new Price(order.Price));
    //            }
    //            break;
    //        case OrderType.Stop:
    //            {
    //                message.set(new OrdType(OrdType.STOP));
    //                message.set(new StopPx(order.StopPrice));
    //            }
    //            break;
    //        case OrderType.StopLimit:
    //            {
    //                message.set(new OrdType(OrdType.STOP_LIMIT));
    //                message.set(new Price(order.Price));
    //                message.set(new StopPx(order.StopPrice));
    //            }
    //            break;
    //    }

    //    message.set(new OrderQty(order.Qty));

    //    switch (order.Instrument.Type)
    //    {
    //        case InstrumentType.Stock:
    //            {
    //                message.set(new SecurityType(SecurityType.COMMON_STOCK));
    //            }
    //            break;
    //        case InstrumentType.Index:
    //            {
    //                message.set(new SecurityType("IDX"));
    //            }
    //            break;
    //        case InstrumentType.FX:
    //            {
    //                message.set(new SecurityType(SecurityType.FOREIGN_EXCHANGE_CONTRACT));
    //            }
    //            break;
    //        case InstrumentType.Futures:
    //            {
    //                message.set(new SecurityType(SecurityType.FUTURE));
    //                message.set(new MaturityMonthYear(order.Instrument.Maturity.ToString("yyyyMM")));
    //            }
    //            break;
    //        case InstrumentType.Option:
    //            {
    //                message.set(new SecurityType(SecurityType.OPTION));
    //                message.set(new MaturityMonthYear(order.Instrument.Maturity.ToString("yyyyMM")));

    //                switch (order.Instrument.PutCall)
    //                {
    //                    case PutCall.Put:
    //                        message.set(new PutOrCall(PutOrCall.PUT));
    //                        break;
    //                    case PutCall.Call:
    //                        message.set(new PutOrCall(PutOrCall.CALL));
    //                        break;
    //                }

    //                message.set(new StrikePrice(order.Instrument.Strike));
    //            }
    //            break;
    //    }

    //    if (order.Account != string.Empty)
    //        message.set(new Account(order.Account));
    //    else
    //        message.set(new Account(provider.Account));

    //    message.set(new Rule80A(provider.Rule80A));
    //    message.set(new CustomerOrFirm(provider.CustomerOrFirm));

    //    if (provider.ClearingAccount != string.Empty)
    //        message.set(new ClearingAccount(provider.ClearingAccount));

    //    orders.Add(clOrdID, order);

        FIX::Session::sendToTarget(message);
    }

    vector<string> availableExchanges() const {
        return vector<string>();
    }

    vector<std::string> availableInstruments() const {
        std::string reqID = FreeQuant::toGuidString();
        FIX44::SecurityListRequest message;
        message.set(FIX::SecurityReqID(reqID));
        message.set(FIX::SecurityListRequestType(FIX::SecurityListRequestType_ALL_SECURITIES));
        FIX::Session::sendToTarget(message);
        return vector<string>();
    }

    void openOrders() const {

    }

    void updateIntrument(std::string symbol, bool block) {
        FIX44::SecurityDefinitionRequest message;
        message.set(FIX::SecurityReqID("guud"));
        message.set(FIX::SecurityRequestType(FIX::SecurityRequestType_SYMBOL));
        message.set(FIX::Symbol(symbol));
        FIX::Session::sendToTarget(message);
    }

    void updateIntrument(FreeQuant::Instrument& instrument) {
        FIX44::SecurityDefinitionRequest message;
        string id = FreeQuant::createGuid();
        message.set(FIX::SecurityReqID(id));
        message.set(FIX::SecurityRequestType(FIX::SecurityRequestType_SYMBOL));
        message.set(FIX::Symbol(instrument.symbol()));

        try {
            FIX::Session::sendToTarget(message);
        } catch (FIX::SessionNotFound&) {}
    }

private:
    void onCreate(const FIX::SessionID&) {

    }

    void onLogon(const FIX::SessionID&) {
        cerr << "onLogon" << endl;
    }

    void onLogout(const FIX::SessionID&) {
        cerr << "onLogout" << endl;
    }

    void toAdmin(FIX::Message& message, const FIX::SessionID& sessionId) {

    }

    void toApp(FIX::Message& message, const FIX::SessionID& sessionId) throw(FIX::DoNotSend) {
        try {
            FIX::PossDupFlag possDupFlag;
            message.getHeader().getField(possDupFlag);
            if (possDupFlag) throw FIX::DoNotSend();
        }
        catch (FIX::FieldNotFound&) {}
    }

    void fromAdmin(const FIX::Message& message, const FIX::SessionID& sessionId)
            throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon) {
        crack(message, sessionId);
    }

    void fromApp(const FIX::Message& message, const FIX::SessionID& sessionId)
            throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType) {
        crack(message, sessionId);
    }

    void onMessage(const FIX44::MarketDataRequestReject& message, const FIX::SessionID& sessionID) {
        FIX::MDReqID mdRegID;
        FIX::MDReqRejReason mdReqRejReason;
        FIX::Text text;
        if (message.isSet(mdRegID)) {

        }
        if (message.isSet(mdReqRejReason)) {

        }
        if (message.isSet(text)) {

        }
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

    void onMessage(const FIX44::ExecutionReport& message, const FIX::SessionID& sessionID) {
        FIX::ExecType execType;
        message.get(execType);

        switch (execType) {
        case FIX::ExecType_NEW:
            break;
        case FIX::ExecType_REJECTED:
            break;
        case FIX::ExecType_CANCELED:
        case FIX::ExecType_EXPIRED:
        case FIX::ExecType_REPLACED:
        case FIX::ExecType_FILL:
        case FIX::ExecType_PARTIAL_FILL:
        case FIX::ExecType_PENDING_CANCEL:
            \
        default:
            break;
        }
    }

    void onMessage(const FIX44::MarketDataIncrementalRefresh& message, const FIX::SessionID& sessionID) {
        FIX::NoMDEntries noMDEntries;
        message.get(noMDEntries);

        for (int i = 1; i <= noMDEntries; i++) {
            FIX44::MarketDataIncrementalRefresh::NoMDEntries group;
            message.getGroup(i, group);
            FIX::MDEntryID mdEntryID;
            group.get(mdEntryID);
            FIX::MDUpdateAction mdUpdateAction;
            group.get(mdUpdateAction);
            switch (mdUpdateAction) {
            case FIX::MDUpdateAction_NEW:
                break;
            case FIX::MDUpdateAction_CHANGE:
            default:
                break;
            }
        }
    //    if (noMDEntries.getValue() != 1) {
    //        std::cout << "NoMDEntries in MarketDataIncrementalRefresh is not 1!" <<std::endl;
    //        return;
    //    }
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

    void onMessage(const FIX44::MarketDataSnapshotFullRefresh& message, const FIX::SessionID &) {
        std::cout << "FixTradeProvider::onMessage(const FIX44::MarketDataSnapshotFullRefresh" << std::endl;

        FIX::NoMDEntries entries;
        message.get(entries);

        for (int i = 1; i <= entries; i++) {
            FIX44::MarketDataSnapshotFullRefresh::NoMDEntries group;
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
        FIX::Symbol symbol;
        message.get(symbol);
    }

    void onMessage(const FIX44::OrderCancelReject&, const FIX::SessionID&) {

    }

    void onMessage(const FIX44::SecurityList& message, const FIX::SessionID& sessionID) {
        vector<string> symbols;
        FIX::NoRelatedSym noRelatedSym;
        message.get(noRelatedSym);
        for (int i = 1; i <= noRelatedSym; i++) {
            FIX44::SecurityList::NoRelatedSym group;
            message.getGroup(i, group);
            FIX::Symbol symbol;
            group.get(symbol);
            symbols.push_back(symbol.getValue());
        }

    }

    void onMessage(const FIX44::SecurityDefinition& message, const FIX::SessionID& sessionID) {
        FIX::Currency currency;
        FIX::SecurityType securityType;
        FIX::StrikePrice strikePrice;

        message.get(currency);
        message.get(securityType); // FIX::SecurityType_FUTURE
        message.get(strikePrice);

    }

    FIX::SessionSettings _settings;
    FIX::FileStoreFactory _storeFactory;
    FIX::SocketInitiator _initiator;
    FIX::SessionID _sessionID;
};

FixTradeProvider::FixTradeProvider(FreeQuant::TradeProvider::Callback *callback) :
    _impl(new FixTradeProvider::Impl("", callback)) {
}

FixTradeProvider::FixTradeProvider(std::string connection) {
    std::map<string, string> params = parseParamsFromString(connection);
    stringstream ss;
    ss << "[DEFAULT]" << endl
       << "ConnectionType=initiator" << endl
       << "ReconnectInterval=60" << endl
       << "SenderCompID=" << "ME" <<  endl
       << "[SESSION]" << endl
       << "BeginString=FIX.4.4" << endl
       << "TargetCompID=" << "FQ" << endl
       << "DataDictionary=FIX44.xml" << endl
       << "StartTime=00:00:01" << endl
       << "EndTime=23:59:59" << endl
       << "HeartBtInt=20" << endl
       << "FileStorePath=." << endl
       << "SocketConnectPort=" << 7711 << endl
       << "SocketConnectHost=" << "127.0.0.1" << endl;
    _impl = new FixTradeProvider::Impl(ss, 0);
}

FixTradeProvider::~FixTradeProvider() {
    delete _impl;
    _impl = 0;
}

void FixTradeProvider::connect() {
    _impl->connect();
}

void FixTradeProvider::disconnect() {
    _impl->disconnect();
}

bool FixTradeProvider::isConnected() const {
    return _impl->isConnected();
}

void FixTradeProvider::logon() {
    _impl->logon();
}

void FixTradeProvider::logout() {
    _impl->logout();
}

std::vector<std::string> FixTradeProvider::availableExchanges() const {
    return std::vector<std::string>();
}

std::vector<std::string> FixTradeProvider::availableInstruments() const {
    return std::vector<std::string>();
}

void FixTradeProvider::sendOrder(FreeQuant::Order& order) {

}

void FixTradeProvider::cancelOrder(FreeQuant::Order& order) {

}

void FixTradeProvider::replaceOrder(FreeQuant::Order& order) {

}

void FixTradeProvider::subscribe(std::vector<std::string> symbols) {

}

void FixTradeProvider::unsubscribe(std::vector<std::string> symbols) {

}

void FixTradeProvider::updateIntrument(std::string symbol, bool block) {

}

void FixTradeProvider::updateIntrument(FreeQuant::Instrument& instrument) {
    _impl->updateIntrument(instrument);
}

} // namespace FreeQuant
