#include <quickfix/Application.h>
#include <quickfix/MessageCracker.h>
#include <quickfix/SessionFactory.h>
#include <quickfix/SessionSettings.h>
#include <quickfix/SocketInitiator.h>
#include <quickfix/FileStore.h>
#include <quickfix/FileLog.h>
#include <quickfix/fix42/NewOrderSingle.h>

#include "fixtradeprovider.h"

using namespace std;

namespace FreeQuant { namespace Trade {

class FixApp : public FIX::Application, public FIX::MessageCracker {
public:
    explicit FixApp() {

    }

    virtual ~FixApp() {
    }
    void run();

private:
    void onCreate(const FIX::SessionID&) {}
    void onLogon(const FIX::SessionID& sessionID) {
        cout << "Logon - " << sessionID << endl;
//        SetEvent(hEventWork);
    }

    void onLogout(const FIX::SessionID& sessionID) {
        cout << "Logout - " << sessionID << std::endl;
    }

    void toAdmin(FIX::Message& msg, const FIX::SessionID&) {
        FIX::MsgType msgType;
        msg.getHeader().getField( msgType );
        if(msgType == FIX::MsgType_Logon)
        {
            char szUserName[32]  = {0};
            char szPassword[32]  = {0};
            char szInputType[32] = {0};
            char szResetSeqNumFlag[5] = {0};

            char *g_pszCfgFileName = "./Clint_pt.cfg";

//            GetPrivateProfileString("testdata","UserName"  ,"", szUserName,  sizeof(szUserName)-1, g_pszCfgFileName);
//            GetPrivateProfileString("testdata","Password"  ,"", szPassword,  sizeof(szPassword)-1, g_pszCfgFileName);
//            GetPrivateProfileString("testdata","InputType" ,"", szInputType, sizeof(szInputType)-1,g_pszCfgFileName);
//            GetPrivateProfileString("testdata","ResetSeqNumFlag" ,"Y", szResetSeqNumFlag, sizeof(szResetSeqNumFlag)-1,g_pszCfgFileName);

            char szValue[1024] = {0};
//            _snprintf(szValue, sizeof(szValue)-1, "%s:%s:%s:",szInputType, szUserName,szPassword);
            msg.setField(FIX::FIELD::RawData, szValue);
            msg.setField(FIX::FIELD::ResetSeqNumFlag,szResetSeqNumFlag);
            msg.setField(FIX::FIELD::EncryptMethod,"0");
            std::string messageString = msg.toString();
            cout << "\n发送登录消息:\n" << messageString << endl;
        }
        if(msgType == FIX::MsgType_Logout)
        {
            std::string messageString = msg.toString();
            cout << "\n发送退出消息:\n" << messageString << endl;
        }

    }

    void toApp(FIX::Message& message, const FIX::SessionID& sessionID ) throw(FIX::DoNotSend) {
        FIX::MsgType msgType;
        message.getHeader().getField( msgType );
        std::string messageString = message.toString();
        if(msgType == "D")
        {
            cout << "\n发送委托消息:\n" << messageString << endl;
        }
        if(msgType == "F")
        {
            cout << "\n发送撤单消息:\n" << messageString << endl;
        }
        if(msgType == "UAN")
        {
            cout << "\n发送资金股份查询消息:\n" << messageString << endl;
        }
        if(msgType == "H")
        {
            cout << "\n发送委托状态查询消息:\n" << messageString << endl;
        }
    }

    void fromAdmin(const FIX::Message& message, const FIX::SessionID& sessionID)
        throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon ) {
        FIX::MsgType msgType;
        FIX::PosReqType posReqType;
        message.getHeader().getField( msgType );
        std::string messageString = message.toString();
        if(msgType == "8")
            cout << "\n收到执行回报消息:\n" << messageString << endl;

        if(msgType == "UAP")
            cout << "\n收到资金股份查询应答消息:\n" << messageString << endl;
    }

    void fromApp(const FIX::Message& message, const FIX::SessionID& sessionID)
        throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType) {
        FIX::MsgType msgType;
        FIX::PosReqType posReqType;
        message.getHeader().getField( msgType );
        std::string messageString = message.toString();
        if(msgType == "8")
            cout << "\n收到执行回报消息:\n" << messageString << endl;

        if(msgType == "UAP")
            cout << "\n收到资金股份查询应答消息:\n" << messageString << endl;

    }
};

FixTradeProvider::FixTradeProvider() {
    string config = "config.fix";
    m_settings = new FIX::SessionSettings(config);
    m_storeFactory = new FIX::FileStoreFactory(*m_settings);
    m_initiator = new FIX::SocketInitiator(*this, *m_storeFactory, *m_settings);
}

FixTradeProvider::~FixTradeProvider() {
    delete m_initiator;
    delete m_storeFactory;
    delete m_initiator;
}

void FixTradeProvider::run() {
    string file = "config";
    FIX::SessionSettings settings(file);
    FIX::FileStoreFactory storeFactory(settings);
      FIX::FileLogFactory logFactory(settings);
      FIX::SocketInitiator initiator(*app, storeFactory, settings, logFactory);
      string senderCompID = "sender";
//      char szSenderCompID[32] = {0};
//      GetPrivateProfileString("SESSION","SenderCompID", "", szSenderCompID, sizeof(szSenderCompID)-1, "./Clint_pt.cfg");
      string targetCompID = "target";
//      char szTargetCompID[32] = {0};
//      GetPrivateProfileString("SESSION","TargetCompID", "", szTargetCompID, sizeof(szTargetCompID)-1, "./Clint_pt.cfg");

      FIX::SessionID sessionID("FIX.4.2", senderCompID, targetCompID);
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
    m_initiator->start();
}

void FixTradeProvider::disconnect() {
    m_initiator->stop();
}

bool FixTradeProvider::isConnected() const {

}

void FixTradeProvider::onCreate(const FIX::SessionID&) {
    cerr << "onCreate" << endl;
}

void FixTradeProvider::onLogon(const FIX::SessionID&) {
    cerr << "onLogon" << endl;
}

void FixTradeProvider::onLogout(const FIX::SessionID&) {
    cerr << "onLogout" << endl;
}

void FixTradeProvider::toAdmin(FIX::Message&, const FIX::SessionID&) {

}

void FixTradeProvider::toApp(FIX::Message&, const FIX::SessionID&) throw(FIX::DoNotSend) {

}

void FixTradeProvider::fromAdmin(const FIX::Message&, const FIX::SessionID&)
    throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon) {

}

void FixTradeProvider::fromApp( const FIX::Message&, const FIX::SessionID& )
    throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType) {

}


}}
