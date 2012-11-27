#include <quickfix/Application.h>
#include <quickfix/Exceptions.h>
#include <quickfix/FileStore.h>
#include <quickfix/FileLog.h>
#include <quickfix/Message.h>
#include <quickfix/MessageCracker.h>
#include <quickfix/SessionFactory.h>
#include <quickfix/SessionSettings.h>
#include <quickfix/SocketInitiator.h>
#include <quickfix/SessionID.h>

#include <quickfix/fix44/Logon.h>
#include <quickfix/fix44/Logout.h>
#include <quickfix/fix44/MarketDataRequest.h>
#include <quickfix/fix44/MarketDataRequestReject.h>
#include <quickfix/fix44/MarketDataSnapshotFullRefresh.h>
#include <quickfix/fix44/MarketDataIncrementalRefresh.h>

#include <freequant/marketdata/MarketDataProvider.h>
#include <freequant/utils/Utility.h>
#include <freequant/strategy/Instrument.h>

#include "FixProviderImpl.h"

namespace FreeQuant { namespace Detail {

FixProviderImpl::FixProviderImpl(std::istream& istream, MarketDataProvider::Callback *callback) :
    _settings(istream), _storeFactory(_settings),
    _initiator(*this, _storeFactory, _settings),
    _callback(callback) {
}

FixProviderImpl::FixProviderImpl(std::istream& istream, TradeProvider::Callback *callback) :
    _settings(istream), _storeFactory(_settings),
    _initiator(*this, _storeFactory, _settings),
    _tcallback(callback) {
}

FixProviderImpl::~FixProviderImpl() {

}

void FixProviderImpl::setCallback(FreeQuant::TradeProvider::Callback *callback) {
    _tcallback = callback;
}

void FixProviderImpl::setCallback(FreeQuant::MarketDataProvider::Callback *callback) {
    _callback = callback;
}

void FixProviderImpl::subscribe(std::vector<std::string> symbols) {
    std::cout << __FUNCTION__ << std::endl;
    FIX44::MarketDataRequest message;
    message.set(FIX::MDReqID(FreeQuant::createGuid()));
    message.set(FIX::SubscriptionRequestType(FIX::SubscriptionRequestType_SNAPSHOT_PLUS_UPDATES));
    message.set(FIX::MarketDepth(0));
    message.set(FIX::MDUpdateType(FIX::MDUpdateType_FULL_REFRESH));

    std::vector<char> types;
    types.push_back(FIX::MDEntryType_OPENING_PRICE);
    types.push_back(FIX::MDEntryType_CLOSING_PRICE);
    for (auto i = types.begin(); i != types.end(); ++i) {
        FIX44::MarketDataRequest::NoMDEntryTypes group;
        FIX::MDEntryType type(*i);
        group.set(type);
        message.addGroup(group);
    }

    for (auto i = symbols.begin(); i != symbols.end(); i++) {
        FIX44::MarketDataRequest::NoRelatedSym group;
        group.set(FIX::Symbol(*i));
        message.addGroup(group);
    }

//                std::string uuid = FreeQuant::toGuidString();
//                FIX::MDReqID mdReqId(uuid);
//                FIX::SubscriptionRequestType subType(FIX::SubscriptionRequestType_SNAPSHOT_PLUS_UPDATES);
//                FIX::MarketDepth marketDepth(1);

//                FIX44::MarketDataRequest message(mdReqId, subType, marketDepth);

//                message.set(FIX::MDUpdateType(FIX::MDUpdateType_INCREMENTAL_REFRESH));
//                message.set(FIX::AggregatedBook(true));
//                string s;
//                s.append(1, FIX::Scope_LOCAL);

//                FIX::Scope scope(s);
//                message.set(scope);

//                message.set(FIX::MDImplicitDelete(false));

//                FIX44::MarketDataRequest::NoMDEntryTypes typeGroup;
//                typeGroup.set(FIX::MDEntryType(FIX::MDEntryType_OPENING_PRICE));
//                message.addGroup(typeGroup);
//                typeGroup.set(FIX::MDEntryType(FIX::MDEntryType_CLOSING_PRICE));
//                message.addGroup(typeGroup);
//                typeGroup.set(FIX::MDEntryType(FIX::MDEntryType_TRADING_SESSION_HIGH_PRICE));
//                message.addGroup(typeGroup);
//                typeGroup.set(FIX::MDEntryType(FIX::MDEntryType_TRADING_SESSION_LOW_PRICE));
//                message.addGroup(typeGroup);
//                typeGroup.set(FIX::MDEntryType(FIX::MDEntryType_BID));
//                message.addGroup(typeGroup);
//                typeGroup.set(FIX::MDEntryType(FIX::MDEntryType_OFFER));
//                message.addGroup(typeGroup);
//                typeGroup.set(FIX::MDEntryType(FIX::MDEntryType_TRADE_VOLUME));
//                message.addGroup(typeGroup);
//                typeGroup.set(FIX::MDEntryType(FIX::MDEntryType_OPEN_INTEREST));
//                message.addGroup(typeGroup);

//                FIX44::MarketDataRequest::NoRelatedSym symGroup;
//                symGroup.set(FIX::Symbol("GOOG"));
//                message.addGroup(symGroup);
//                symGroup.set(FIX::Symbol("IF1210"));
//                message.addGroup(symGroup);
    FIX::SessionID sessionID;
    sessionID.fromString(_sessionString);
    try {
        FIX::Session::sendToTarget(message, sessionID);
    } catch (FIX::SessionNotFound&) {}
}

void FixProviderImpl::unsubscribe(std::vector<std::string> symbols) {
    std::string uuid = FreeQuant::toGuidString();
    FIX::MDReqID mdReqId(uuid);
    FIX::SubscriptionRequestType subType(FIX::SubscriptionRequestType_DISABLE_PREVIOUS_SNAPSHOT_PLUS_UPDATE_REQUEST);
    FIX::MarketDepth marketDepth(1);

    FIX44::MarketDataRequest message(mdReqId, subType, marketDepth);

    message.set(FIX::MDUpdateType(FIX::MDUpdateType_INCREMENTAL_REFRESH));
    message.set(FIX::AggregatedBook(true));
    std::string s;
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


    FIX::SessionID sessionID;
    sessionID.fromString(_sessionString);
    try {
        FIX::Session::sendToTarget(message, sessionID);
    } catch (FIX::SessionNotFound&) {}
}

void FixProviderImpl::connect() {
    _initiator.start();
}

void FixProviderImpl::disconnect() {
    _initiator.stop();
}

bool FixProviderImpl::isConnected() const {
    return _initiator.isLoggedOn();
}

void FixProviderImpl::sendOrder(const FreeQuant::Order& order) {
    FIX44::NewOrderSingle message;
    message.set(FIX::ClOrdID(FreeQuant::createGuid()));
    FIX::Side side;
    if (order.side() == FreeQuant::Order::Buy) {
        side = FIX::Side_BUY;
    } else {
        side = FIX::Side_SELL;
    }
    message.set(side);

    FIX::OrdType type;
    switch (order.type()) {
    case FreeQuant::Order::Market:
        type = FIX::OrdType_MARKET;
    default:
        break;
    }
}


void FixProviderImpl::onCreate(const FIX::SessionID& sessionID) {
    _sessionString = sessionID.toString();
    std::cout << __FUNCTION__ << ": " << sessionID << std::endl;
}

void FixProviderImpl::onLogon(const FIX::SessionID& sessionID) {
    std::cout << __FUNCTION__ << ": " << sessionID << std::endl;
    if (_callback) _callback->onConnected();
}

void FixProviderImpl::onLogout(const FIX::SessionID& sessionID) {
    std::cout << __FUNCTION__ << ": " << sessionID << std::endl;
}

void FixProviderImpl::toAdmin(FIX::Message& message, const FIX::SessionID& sessionID) {
    crack(message, sessionID);
}

void FixProviderImpl::toApp(FIX::Message& message, const FIX::SessionID& sessionId) throw(FIX::DoNotSend) {
    crack(message, sessionId);
}

void FixProviderImpl::fromAdmin(const FIX::Message& message, const FIX::SessionID& sessionId)
        throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon) {
    crack(message, sessionId);
}

void FixProviderImpl::fromApp(const FIX::Message& message, const FIX::SessionID& sessionId)
        throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType) {
    crack(message, sessionId);
}

void FixProviderImpl::onMessage(FIX44::Logon& message, const FIX::SessionID& sessionID) {
    const FIX::Dictionary& dictionary = _settings.get(sessionID);
    if (dictionary.has("Username")) {
        FIX::Username username = dictionary.getString("Username");
        message.set(username);
    }
    if (dictionary.has("Password")) {
        FIX::Password password = dictionary.getString("Password");
        message.set(password);
    }
}

void FixProviderImpl::onMessage(const FIX44::MarketDataRequestReject&, const FIX::SessionID&) {}
void FixProviderImpl::onMessage(const FIX44::MarketDataIncrementalRefresh&, const FIX::SessionID&) {}

void FixProviderImpl::onMessage(const FIX44::MarketDataSnapshotFullRefresh& message, const FIX::SessionID &sessionID) {
    std::cout << "MarketDataSnapshotFullRefresh" << ": " << sessionID << std::endl;

    FIX::Symbol symbol;
    message.get(symbol);

    double close;
    double open;
    FIX::NoMDEntries entries;
    message.get(entries);
    for (int i = 1; i <= entries; i++) {
        FIX44::MarketDataSnapshotFullRefresh::NoMDEntries group;
        message.getGroup(i, group);
        FIX::MDEntryDate mdEntryDate;
        FIX::MDEntryTime mdEntryTime;
        FIX::MDEntryType mdEntryType;
        FIX::MDEntryPx mdEntryPx;
        group.get(mdEntryType);
        group.get(mdEntryPx);

        switch (mdEntryType) {
        case FIX::MDEntryType_CLOSING_PRICE:
            close = mdEntryPx;
            std::cout << "close" << mdEntryPx << std::endl;
            break;
        case FIX::MDEntryType_OPENING_PRICE:
            open = mdEntryPx;
            std::cout << "open" << mdEntryPx << std::endl;
            break;
        default:
            break;
        }
    }


//        Bar bar(1,2,1,1,1);
    Bar bar(symbol, FreeQuant::DateTime(), open, 1, 1, close, 1);
    if (_callback) {
        _callback->onBar(bar);
    }
}


}} // namespace FreeQuant
