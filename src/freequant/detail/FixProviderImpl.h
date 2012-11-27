#ifndef FQ_DETAIL_FIXPROVIDERIMPL_H
#define FQ_DETAIL_FIXPROVIDERIMPL_H

#include <iostream>
#include <string>
#include <vector>

#include <quickfix/Application.h>
#include <quickfix/Exceptions.h>
#include <quickfix/FileStore.h>
#include <quickfix/FileLog.h>
#include <quickfix/Message.h>
#include <quickfix/MessageCracker.h>
#include <quickfix/fix44/NewOrderSingle.h>

#include <freequant/marketdata/MarketDataProvider.h>
#include <freequant/trade/TradeProvider.h>
#include <freequant/utils/Utility.h>

namespace FreeQuant { namespace Detail {

class FixProviderImpl  : private FIX::Application, private FIX::MessageCracker {
public:
    FixProviderImpl(std::istream& istream, MarketDataProvider::Callback *callback = 0);
    FixProviderImpl(std::istream& istream, TradeProvider::Callback *callback = 0);
    virtual ~FixProviderImpl();
    void setCallback(FreeQuant::TradeProvider::Callback *callback);
    void setCallback(FreeQuant::MarketDataProvider::Callback *callback);
    void subscribe(std::vector<std::string> symbols);
    void unsubscribe(std::vector<std::string> symbols);

    void connect();

    void disconnect();

    bool isConnected() const;

    void sendOrder(const FreeQuant::Order& order);
private:
    void onCreate(const FIX::SessionID& sessionID);

    void onLogon(const FIX::SessionID& sessionID);

    void onLogout(const FIX::SessionID& sessionID);

    void toAdmin(FIX::Message& message, const FIX::SessionID& sessionID);

    void toApp(FIX::Message& message, const FIX::SessionID& sessionId) throw(FIX::DoNotSend);

    void fromAdmin(const FIX::Message& message, const FIX::SessionID& sessionId)
            throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon);

    void fromApp(const FIX::Message& message, const FIX::SessionID& sessionId)
            throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType);

    void onMessage(FIX44::Logon& message, const FIX::SessionID& sessionID);

    void onMessage(const FIX44::MarketDataRequestReject&, const FIX::SessionID&);
    void onMessage(const FIX44::MarketDataIncrementalRefresh&, const FIX::SessionID&);

    void onMessage(const FIX44::MarketDataSnapshotFullRefresh& message, const FIX::SessionID &sessionID);
    std::string _sessionString;
    MarketDataProvider::Callback *_callback;
    TradeProvider::Callback *_tcallback;
    FIX::SessionSettings _settings;
    FIX::FileStoreFactory _storeFactory;
    mutable FIX::SocketInitiator _initiator;
};

}} // namespace FreeQuant

#endif // FQ_DETAIL_FIXPROVIDERIMPL_H
