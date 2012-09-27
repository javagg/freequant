#ifndef FQ_TRADE_FIXTRADEPROVIDER_H
#define FQ_TRADE_FIXTRADEPROVIDER_H

#include <quickfix/Application.h>
#include <quickfix/Exceptions.h>
#include <quickfix/FileStore.h>
#include <quickfix/SocketInitiator.h>
#include <quickfix/Message.h>
#include <quickfix/MessageCracker.h>
#include <quickfix/SessionID.h>

#include <fq/trade/tradeprovider.h>

namespace FreeQuant { namespace Trade {

class FixApp;

class FixTradeProvider : public TradeProvider, private FIX::Application, private FIX::MessageCracker {
public:
    FixTradeProvider();
    virtual ~FixTradeProvider();
    void connect();
    void disconnect();
    bool isConnected() const;
    std::string name() const { return "FIX"; }

    void sendOrder();
    void run();

private:
    FixApp *app;

    virtual void onCreate(const FIX::SessionID&);
    virtual void onLogon(const FIX::SessionID&);
    virtual void onLogout(const FIX::SessionID&);
    virtual void toAdmin(FIX::Message&, const FIX::SessionID&);
    virtual void toApp(FIX::Message&, const FIX::SessionID&)
        throw(FIX::DoNotSend);
    virtual void fromAdmin(const FIX::Message&, const FIX::SessionID&)
        throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon);
    virtual void fromApp( const FIX::Message&, const FIX::SessionID& )
        throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType);

    FIX::SessionSettings *m_settings;
    FIX::FileStoreFactory *m_storeFactory;
    FIX::SocketInitiator *m_initiator;
};

}}
#endif // FQ_TRADE_FIXTRADEPROVIDER_H
