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
#include "FixMarketDataProvider.h"
#include <freequant/utils/Utility.h>
#include <freequant/strategy/Instrument.h>

using namespace std;

namespace FreeQuant {

class FixMarketDataProvider::Impl : private FIX::Application, private FIX::MessageCracker {
public:
    Impl(std::string filename, MarketDataProvider::Callback *callback = 0) :
        _settings(filename), _storeFactory(_settings),
        _initiator(*this, _storeFactory, _settings),
        _callback(callback) {
    }

    Impl(std::istream& istream, MarketDataProvider::Callback *callback = 0) :
        _settings(istream), _storeFactory(_settings),
        _initiator(*this, _storeFactory, _settings),
        _callback(callback) {
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
        typeGroup.set(FIX::MDEntryType(FIX::MDEntryType_OPENING));
        message.addGroup(typeGroup);
        typeGroup.set(FIX::MDEntryType(FIX::MDEntryType_CLOSING));
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

        for (auto i = symbols.begin(); i != symbols.end(); i++) {
            auto sym = *i;
            FIX44::MarketDataRequest::NoRelatedSym symGroup;
            symGroup.set(FIX::Symbol(*i));
            message.addGroup(symGroup);
        }

//        FIX44::MarketDataRequest::NoRelatedSym symGroup;
//        symGroup.set(FIX::Symbol("GOOG"));
//        message.addGroup(symGroup);
//        symGroup.set(FIX::Symbol("IF1210"));
//        message.addGroup(symGroup);

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
        typeGroup.set(FIX::MDEntryType(FIX::MDEntryType_OPENING));
        message.addGroup(typeGroup);
        typeGroup.set(FIX::MDEntryType(FIX::MDEntryType_CLOSING));
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
//        logon();

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
        return _initiator.isLoggedOn();
    }

    MarketDataProvider::Callback *_callback;
private:
    void onCreate(const FIX::SessionID&) {}
    void onLogon(const FIX::SessionID&) {}
    void onLogout(const FIX::SessionID&) {}
    void toAdmin(FIX::Message&, const FIX::SessionID&) {}
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

        FIX44::MarketDataIncrementalRefresh::NoMDEntries group;
        message.getGroup(1, group);

        FIX::MDEntryID entryID; group.get(entryID);
        FIX::MDUpdateAction action; group.get(action);

        char actionvalue = action.getValue();//0=New, 1=Update, 2=Delete)
//        std::cout << message.toXML() << std::endl;
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

        Bar bar(1,2,1,1,1);
        if (_callback) {
            _callback->onBar(bar);
        }
    }

    FIX::SessionSettings _settings;
    FIX::FileStoreFactory _storeFactory;
    mutable FIX::SocketInitiator _initiator;
    FIX::SessionID _sessionID;
};

FixMarketDataProvider::FixMarketDataProvider(FreeQuant::MarketDataProvider::Callback *callback) :
    _impl(new FixMarketDataProvider::Impl("", callback)) {
}

FixMarketDataProvider::FixMarketDataProvider(std::string connection, FreeQuant::MarketDataProvider::Callback *callback) {
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
    _impl = new FixMarketDataProvider::Impl(ss, callback);
}

FixMarketDataProvider::~FixMarketDataProvider() {
    delete _impl;
    _impl = 0;
}

void FixMarketDataProvider::connect(bool block) {
    _impl->connect();
}

void FixMarketDataProvider::disconnect(bool block) {
    _impl->disconnect();
}

bool FixMarketDataProvider::isConnected() const {
    return _impl->isConnected();
}

void FixMarketDataProvider::subscribe(std::vector<std::string> symbols) {
    _impl->subscribe(symbols);
}

void FixMarketDataProvider::unsubscribe(std::vector<std::string> symbols) {
    _impl->unsubscribe(symbols);
}

} // namespace FreeQuant
