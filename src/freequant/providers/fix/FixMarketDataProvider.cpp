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
    Impl(std::istream& istream, MarketDataProvider::Callback *callback = 0) :
        _settings(istream), _storeFactory(_settings),
        _initiator(*this, _storeFactory, _settings),
        _callback(callback) {
    }

    virtual ~Impl() {

    }

    void setCallback(FreeQuant::MarketDataProvider::Callback *callback) {
        _callback = callback;
    }

    void subscribe(std::vector<std::string> symbols) {
        cout << __FUNCTION__ << endl;
        FIX44::MarketDataRequest message;
        message.set(FIX::MDReqID(FreeQuant::createGuid()));
        message.set(FIX::SubscriptionRequestType(FIX::SubscriptionRequestType_SNAPSHOT_PLUS_UPDATES));
        message.set(FIX::MarketDepth(0));
        message.set(FIX::MDUpdateType(FIX::MDUpdateType_FULL_REFRESH));

        vector<char> types;
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


        FIX::SessionID sessionID;
        sessionID.fromString(_sessionString);
        try {
            FIX::Session::sendToTarget(message, sessionID);
        } catch (FIX::SessionNotFound&) {}
    }

    void connect() {
        _initiator.start();
    }

    void disconnect() {
        _initiator.stop();
    }

    bool isConnected() const {
        return _initiator.isLoggedOn();
    }

private:
    void onCreate(const FIX::SessionID& sessionID) {
        _sessionString = sessionID.toString();
        cout << __FUNCTION__ << ": " << sessionID << endl;
    }

    void onLogon(const FIX::SessionID& sessionID) {
        cout << __FUNCTION__ << ": " << sessionID << endl;
        if (_callback) _callback->onConnected();
    }

    void onLogout(const FIX::SessionID& sessionID) {
        cout << __FUNCTION__ << ": " << sessionID << endl;
    }

    void toAdmin(FIX::Message& message, const FIX::SessionID& sessionID) {
        crack(message, sessionID);
    }

    void toApp(FIX::Message& message, const FIX::SessionID& sessionId) throw(FIX::DoNotSend) {
        crack(message, sessionId);
    }

    void fromAdmin(const FIX::Message& message, const FIX::SessionID& sessionId)
            throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon) {
        crack(message, sessionId);
    }

    void fromApp(const FIX::Message& message, const FIX::SessionID& sessionId)
            throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType) {
        crack(message, sessionId);
    }

    void onMessage(FIX44::Logon& message, const FIX::SessionID& sessionID) {
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

    void onMessage(const FIX44::MarketDataRequestReject&, const FIX::SessionID&) {}
    void onMessage(const FIX44::MarketDataIncrementalRefresh&, const FIX::SessionID&) {}

    void onMessage(const FIX44::MarketDataSnapshotFullRefresh& message, const FIX::SessionID &sessionID) {
        cout << "MarketDataSnapshotFullRefresh" << ": " << sessionID << endl;

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
                cout << "close" << mdEntryPx << endl;
                break;
            case FIX::MDEntryType_OPENING_PRICE:
                open = mdEntryPx;
                cout << "open" << mdEntryPx << endl;
                break;
            default:
                break;
            }
        }

        Bar bar(symbol, DateTime(), open, 1, 1, close, 1);
        if (_callback) {
            _callback->onBar(bar);
        }
    }

    string _sessionString;
    MarketDataProvider::Callback *_callback;
    FIX::SessionSettings _settings;
    FIX::FileStoreFactory _storeFactory;
    mutable FIX::SocketInitiator _initiator;
};

FixMarketDataProvider::FixMarketDataProvider(std::string connection, FreeQuant::MarketDataProvider::Callback *callback) {
    std::map<string, string> params = parseParamsFromString(connection);
    stringstream ss;
    ss << "[DEFAULT]" << endl
       << "BeginString=FIX.4.4" << endl
       << "ConnectionType=initiator" << endl
       << "ReconnectInterval=60" << endl
       << "SenderCompID=" << params["senderid"] <<  endl
       << "DataDictionary=FIX44.xml" << endl
       << "StartTime=00:00:00" << endl
       << "EndTime=00:00:00" << endl
       << "HeartBtInt=20" << endl
       << "FileStorePath=." << endl
       << "Username=" << params["username"] << endl
       << "Password=" << params["password"] << endl
       << "[SESSION]" << endl
       << "TargetCompID=" << params["targetid"] << endl
       << "SocketConnectPort=" << params["port"] << endl
       << "SocketConnectHost=" << params["host"] << endl;
    _impl.reset(new FixMarketDataProvider::Impl(ss, callback));
}

FixMarketDataProvider::~FixMarketDataProvider() {}
void FixMarketDataProvider::setCallback(FreeQuant::MarketDataProvider::Callback *callback) {
    _impl->setCallback(callback);
}

void FixMarketDataProvider::setCallback(MarketDataProviderCallback *callback) {

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

void FixMarketDataProvider::subscribe(const Symbols& symbols) {
    _impl->subscribe(symbols);
}

void FixMarketDataProvider::unsubscribe(const Symbols& symbols) {
    _impl->unsubscribe(symbols);
}

void FixMarketDataProvider::subscribe(const std::string& symbol) {

}

void FixMarketDataProvider::unsubscribe(const std::string& symbol) {

}

} // namespace FreeQuant
