#include <algorithm>
#include <iostream>

#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

#include <freequant/strategy/Order.h>
#include <freequant/strategy/Position.h>
#include <freequant/strategy/Instrument.h>
#include <freequant/utils/Utility.h>

#include "CtpTradeProvider.h"
#include "ThostFtdcTraderApi.h"

using namespace std;

namespace FreeQuant {

static TThostFtdcOrderRefType orderRef = {};
static long requestId = 0;
static const char *flowPath = "fqctptrader";

class CtpTradeProvider::Impl : public CThostFtdcTraderSpi {
public:
    static const int reqTimeout = 5;
    Impl(const std::string& connection, FreeQuant::TradeProvider::Callback *callback) :
        _connected(false), _callback(callback), _api(0) {
        auto params = FreeQuant::parseParamsFromString(connection);
        _front = params["protocal"] + "://" + params["host"] + ":"  + params["port"]; //"tcp://asp-sim2-front1.financial-trading-platform.com:26213";
        _userId = params["userid"];
        _password = params["password"];
        _brokerId = params["brokerid"];

        _api = CThostFtdcTraderApi::CreateFtdcTraderApi(flowPath);
        _api->RegisterSpi(this);
        _api->RegisterFront(const_cast<char*>(_front.c_str()));
        _api->SubscribePrivateTopic(THOST_TERT_RESTART);
        _api->SubscribePrivateTopic(THOST_TERT_RESTART);
    }

    virtual ~Impl() {
        disconnect();
    }

    bool errorOccurred(CThostFtdcRspInfoField *rspInfo) {
        bool occurred = rspInfo && rspInfo->ErrorID != 0;
        if (occurred) {
            cerr << "--->>> ErrorID=" << rspInfo->ErrorID << ", ErrorMsg=" << rspInfo->ErrorMsg << endl;
        }
        return (rspInfo && rspInfo->ErrorID != 0);
    }

    void connect(std::string connection, bool block = false) {
        if (isConnected()) return;
        auto params = FreeQuant::parseParamsFromString(connection);
        _front = params["protocal"] + "://" + params["host"] + ":"  + params["port"]; //"tcp://asp-sim2-front1.financial-trading-platform.com:26213";
        _userId = params["userid"];
        _password = params["password"];
        _brokerId = params["brokerid"];

        resetApi();
        _api = CThostFtdcTraderApi::CreateFtdcTraderApi("");
        _api->RegisterSpi(this);
        _api->RegisterFront(const_cast<char*>(_front.c_str()));
        _api->SubscribePrivateTopic(THOST_TERT_QUICK);
        _api->SubscribePrivateTopic(THOST_TERT_QUICK);
        _api->Init();

        if (block) {
            boost::unique_lock<boost::mutex> lock(_mutex);
            _condition.wait_for(lock, boost::chrono::seconds(reqTimeout));
            CThostFtdcSettlementInfoConfirmField field = {};
            _brokerId.copy(field.BrokerID, _brokerId.size());
            _userId.copy(field.InvestorID, _userId.size());
            _api->ReqSettlementInfoConfirm(&field, ++requestId);
            _condition.wait_for(lock, boost::chrono::seconds(reqTimeout));
        }
    }

    void resetApi() {
        if (_api) {
            _api->RegisterSpi(0);
            _api->Release();
            _api = 0;
        }
    }

    void connect() {
//        if (isConnected()) return;
//        _api->Init();
    }

    void disconnect() {
        if (!isConnected()) return;

        CThostFtdcUserLogoutField field = {};
        _brokerId.copy(field.BrokerID, _brokerId.size());
        _userId.copy(field.UserID, _userId.size());
        _api->ReqUserLogout(&field, ++requestId);
        boost::unique_lock<boost::mutex> lock(_mutex);
        _condition.wait(lock);
        resetApi();
    }

    bool isConnected() const {
        return _connected;
    }

    void logout() {
        CThostFtdcUserLogoutField req = {};
        _brokerId.copy(req.BrokerID, _brokerId.size());
        _userId.copy(req.UserID, _userId.size());
        int ret = _api->ReqUserLogout(&req, ++requestId);
    }

    std::vector<std::string> availableExchanges() const {
        string exchangeId = "dsf";
        CThostFtdcQryExchangeField field = {};
        exchangeId.copy(field.ExchangeID, exchangeId.size());
        _api->ReqQryExchange(&field, ++requestId);

        return vector<string>();
    }

    std::vector<std::string> availableInstruments() const {
        CThostFtdcQryInstrumentField field;
    //    api->ReqQryInstrument()
        return vector<string>();
    }

    void sendOrder(const FreeQuant::Order& o) {
        CThostFtdcInputOrderField field = {};
        _brokerId.copy(field.BrokerID, _brokerId.size());
        _userId.copy(field.InvestorID, _userId.size());
        o.symbol().copy(field.InstrumentID, o.symbol().size());
        strcpy(field.OrderRef, nextOrderRef());
//        int nextOrderRef = atoi(orderRef);
//        sprintf(orderRef, "%d", ++nextOrderRef);

        if (o.side() == Order::Buy)
            field.Direction = THOST_FTDC_D_Buy;
        else
            field.Direction = THOST_FTDC_D_Sell;

        field.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
        field.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
        switch (o.type()) {
        case Order::Market: {
            field.OrderPriceType = THOST_FTDC_OPT_LastPrice;
            field.LimitPrice = o.price();
        }
        case Order::Limit: {
            field.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
            field.LimitPrice = o.limitPrice();
            break;
        }
        case Order::StopLimit:
        case Order::StopLoss:
            field.StopPrice = o.stopPrice();
            break;
        default:
            break;
        }

        field.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
        field.LimitPrice = o.price();
        field.VolumeTotalOriginal = o.qty();

//        switch (o.timeInForce()) {
//        case Order::DAY:
//            field.TimeCondition = THOST_FTDC_TC_GFD;
//            break;
//        default:
//            break;
//        }
        field.TimeCondition = THOST_FTDC_TC_GFD;
        field.VolumeCondition = THOST_FTDC_VC_AV;
        field.MinVolume = 1;
        field.ContingentCondition = THOST_FTDC_CC_Immediately;
        field.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
        field.IsAutoSuspend = true;
        field.UserForceClose = true;
        int ret = _api->ReqOrderInsert(&field, requestId++);
    }

    void cancelOrder(const FreeQuant::Order& order) {
        CThostFtdcInputOrderActionField req = {};
        _brokerId.copy(req.BrokerID, _brokerId.size());
        _userId.copy(req.InvestorID, _userId.size());
        req.ActionFlag = THOST_FTDC_AF_Delete;

        order.orderId().copy(req.OrderSysID, order.orderId().size());
        req.ActionFlag = THOST_FTDC_AF_Delete;
        order.symbol().copy(req.InstrumentID, order.symbol().size());
        int ret = _api->ReqOrderAction(&req, ++requestId);
    }

    void replaceOrder(const FreeQuant::Order& order) {
        CThostFtdcInputOrderActionField req = {};
        _brokerId.copy(req.BrokerID, _brokerId.size());
        _userId.copy(req.InvestorID, _userId.size());
        req.ActionFlag = THOST_FTDC_AF_Modify;

         int ret = _api->ReqOrderAction(&req, ++requestId);
    }

    void updateAccounts() {

    }

    void updatePosition(std::string symbol) {
        CThostFtdcQryInvestorPositionField req = {};
        _brokerId.copy(req.BrokerID, _brokerId.size());
        _userId.copy(req.InvestorID, _userId.size());
        symbol.copy(req.InstrumentID, symbol.size());
        int ret = _api->ReqQryInvestorPosition(&req, ++requestId);
    }

    void openOrders() {
        CThostFtdcQryOrderField field = {};
        _brokerId.copy(field.BrokerID, _brokerId.size());
        _userId.copy(field.InvestorID, _userId.size());
        string symbol = "IF1212";
        symbol.copy(field.InstrumentID, symbol.size());

        _api->ReqQryOrder(&field, ++requestId);
    }

    void updateIntrument(std::string symbol, bool block = false) {
        CThostFtdcQryInstrumentField field = {};
        symbol.copy(field.InstrumentID, symbol.size());
        _api->ReqQryInstrument(&field, requestId++);
    }

    CThostFtdcTraderApi *_api;

    void OnFrontDisconnected(int reason) {
        _connected = false;
        std::cout << "disconnected: " << reason << std::endl;
    }

    void OnHeartBeatWarning(int timeLapse) { std::cout << "heartbeat: " << timeLapse << std::endl; }
    void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        std::cerr << __FUNCTION__ << std::endl;
        std::cerr << "ErrorCode=" << pRspInfo->ErrorID << "ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
    }

    void OnFrontConnected() {
        std::cout << __FUNCTION__ << std::endl;
        CThostFtdcReqUserLoginField req = {};
        _brokerId.copy(req.BrokerID, _brokerId.size());
        _userId.copy(req.UserID, _userId.size());
        _password.copy(req.Password, _password.size());
        int ret = _api->ReqUserLogin(&req, ++requestId);
    }

    void OnRspUserLogin(CThostFtdcRspUserLoginField *rspUserLogin, CThostFtdcRspInfoField *rspInfo, int nRequestID, bool last) {
        std::cout << __FUNCTION__ << std::endl;
        if (!errorOccurred(rspInfo) && last) {
            _frontId = rspUserLogin->FrontID;
            _sessionId = rspUserLogin->FrontID;

            nextOrderRef(rspUserLogin->MaxOrderRef);
            const char *tradingDay = _api->GetTradingDay();
            std::cout << "TradingDay: " << tradingDay << std::endl;
            _connected = true;

            boost::unique_lock<boost::mutex> lock(_mutex);
            _condition.notify_all();
        }

        CThostFtdcQryTradingAccountField field = {};
        _brokerId.copy(field.BrokerID, _brokerId.size());
        _userId.copy(field.InvestorID, _userId.size());
        _api->ReqQryTradingAccount(&field, ++requestId);
    }

    void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *confirm,
        CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        boost::unique_lock<boost::mutex> lock(_mutex);
        _condition.notify_all();
    }

    void OnRspUserLogout(CThostFtdcUserLogoutField *userLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        cout << userLogout->UserID << endl;
         if (!errorOccurred(pRspInfo) && bIsLast) {
            boost::unique_lock<boost::mutex> lock(_mutex);
            _condition.notify_one();
         }
    }

    void OnRspQryInstrument(CThostFtdcInstrumentField *i, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        if (!errorOccurred(pRspInfo) && bIsLast) {
             std::cout << "InstrumentID: " << i->InstrumentID  << std::endl
                    << "ExchangeID: " << i->ExchangeID  << std::endl
                    << "ExchangeInstID: " << i->ExchangeInstID  << std::endl
                    << "OpenDate: " << i->OpenDate  << std::endl
                    << "ExpireDate: " << i->ExpireDate  << std::endl
                    << "InstLifePhase: " << i->InstLifePhase  << std::endl
                    << "InstrumentName: " << i->InstrumentName  << std::endl
                    << "ProductID: " << i->ProductID  << std::endl
                    << "LongMarginRatio: " << i->LongMarginRatio  << std::endl
                   << "ShortMarginRatio: " << i->ShortMarginRatio  << std::endl
                   << "VolumeMultiple: " << i->VolumeMultiple  << std::endl
                   << "MaxLimitOrderVolume: " << i->MaxLimitOrderVolume  << std::endl
                   << "ProductClass: " << i->ProductClass  << std::endl
                  << "PositionType: " << i->PositionType  << std::endl
                   << "PriceTick: " << i->PriceTick  << std::endl
                       ;
             CThostFtdcQryInstrumentMarginRateField field = {};
             _brokerId.copy(field.BrokerID, _brokerId.size());
             _userId.copy(field.InvestorID, _userId.size());
             strcpy(field.InstrumentID, i->InstrumentID);

              std::cout<< "ReqQryInstrumentMarginRate......." << std::endl;
             _api->ReqQryInstrumentMarginRate(&field, ++requestId);
              std::cout<< "after ReqQryInstrumentMarginRate......." << std::endl;

        }
        ////        FreeQuant::Instrument instrument(i->InstrumentID);
//        instrument.setExchange(i->ExchangeInstID);
//        instrument.setName(i->InstrumentName);
////        instrument.setExpireDate(FreeQuant::DateTime(i->ExpireDate));
//        instrument.setMultipler(i->VolumeMultiple);
//        instrument.setTickSize(i->PriceTick);
//        instrument.setMargin(i->LongMarginRatio);
//        instrument.setType(FreeQuant::Instrument::Stock);
//        instrument.setCurrency("RMB");
   }

    void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *i, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        std::cout << __FUNCTION__ << std::endl;
        if (!errorOccurred(pRspInfo) && bIsLast) {
             std::cout << "InstrumentID: " << i->InstrumentID  << std::endl
                    << "LongMarginRatioByMoney: " << i->LongMarginRatioByMoney  << std::endl
                     << "LongMarginRatioByVolume: " << i->LongMarginRatioByVolume  << std::endl
                    << "InvestorID: " << i->InvestorID  << std::endl
                 ;

             CThostFtdcQryInstrumentCommissionRateField field = {};
             _brokerId.copy(field.BrokerID, _brokerId.size());
             _userId.copy(field.InvestorID, _userId.size());
             strcpy(field.InstrumentID, i->InstrumentID);

            _api->ReqQryInstrumentCommissionRate(&field, ++requestId);
         }
    }

    void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *i, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        std::cout << __FUNCTION__ << std::endl;
        if (!errorOccurred(pRspInfo) && bIsLast) {
             std::cout << "InstrumentID: " << i->InstrumentID  << std::endl
                       << "OpenRatioByMoney: " << i->OpenRatioByMoney  << std::endl
                        << "OpenRatioByVolume: " << i->OpenRatioByVolume  << std::endl
                       << "InvestorID: " << i->InvestorID  << std::endl
                          ;
         }
    }


    void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {

        std::cout << "Balance: " << pTradingAccount->Balance << std::endl
                  << "AccountID: "   << pTradingAccount->AccountID << std::endl
                  << "Deposit: "   << pTradingAccount->Deposit << std::endl
                  << "CashIn: "   << pTradingAccount->CashIn << std::endl;
    }

    void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        std::cout << __FUNCTION__ << std::endl;
        if (!errorOccurred(pRspInfo) && bIsLast) {

        }
    }

    void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        if (!errorOccurred(pRspInfo) && bIsLast) {
            CThostFtdcOrderField order = *pOrder;
            cout << "BrokerOrderSeq:"<<order.BrokerOrderSeq<<endl
                 << "OrderSysID:"<<order.OrderSysID<<endl
                 << "OrderStatus:"<<order.OrderStatus<<endl
                << "OrderSubmitStatus:"<<order.OrderSubmitStatus<<endl
                ;
        }
    }

    void OnRtnOrder(CThostFtdcOrderField *pOrder) {
        std::cout << __FUNCTION__ << std::endl;
        CThostFtdcOrderField order = *pOrder;

        cout << "BrokerOrderSeq:"<<order.BrokerOrderSeq<<endl
             << "OrderSysID:"<<order.OrderSysID<<endl
             << "OrderStatus:"<<order.OrderStatus<<endl
            << "OrderSubmitStatus:"<<order.OrderSubmitStatus<<endl
            ;
//      bool founded=false;    unsigned int i=0;
//      for(i=0; i<orderList.size(); i++){
//        if(orderList[i]->BrokerOrderSeq == order->BrokerOrderSeq) {
//          founded=true;    break;
//        }
//      }
//      if(founded) orderList[i]= order;
//      else  orderList.push_back(order);

    }

    void OnRtnTrade(CThostFtdcTradeField *pTrade) {
      CThostFtdcTradeField trade = *pTrade;
//      bool founded=false;     unsigned int i=0;
//      for(i=0; i<tradeList.size(); i++){
//        if(tradeList[i]->TradeID == trade->TradeID) {
//          founded=true;   break;
//        }
//      }
//      if(founded) tradeList[i] = trade;
//      else  tradeList.push_back(trade);
      cerr<<"OnRtnTrade...:"<<trade.TradeID<<endl;
    }

private:
    TThostFtdcOrderRefType& nextOrderRef(TThostFtdcOrderRefType firstOrderRef = 0) {
        if (firstOrderRef)
            std::memcpy(_orderRef, firstOrderRef, sizeof(_orderRef));
        int nextOrderRef = atoi(_orderRef);
        std::sprintf(_orderRef, "%d", ++nextOrderRef);
        return _orderRef;
    }

    bool _connected;
    bool _settlementConfirmed;

    FreeQuant::TradeProvider::Callback *_callback;
    std::string _brokerId;
    std::string _userId;
    std::string _password;
    std::string _front;
    TThostFtdcFrontIDType _frontId;
    TThostFtdcSessionIDType	_sessionId;
    TThostFtdcOrderRefType _orderRef;

    boost::mutex _mutex;
    boost::condition_variable _condition;
};

CtpTradeProvider::CtpTradeProvider(const std::string& connection, FreeQuant::TradeProvider::Callback *callback) :
    _impl(new CtpTradeProvider::Impl(connection, callback)) {

}

CtpTradeProvider::~CtpTradeProvider() {}

void CtpTradeProvider::connect() {
    _impl->connect();
}

void CtpTradeProvider::connect(const std::string& connection, bool block) {
    _impl->connect(connection, block);
}

void CtpTradeProvider::disconnect() {
    _impl->disconnect();
}

bool CtpTradeProvider::isConnected() const {
    return _impl->isConnected();
}

vector<string> CtpTradeProvider::availableExchanges() const {
    return _impl->availableExchanges();
}

vector<string> CtpTradeProvider::availableInstruments() const {
    return _impl->availableInstruments();
}

void CtpTradeProvider::updateAccounts() {
    _impl->updateAccounts();

 }

void CtpTradeProvider::updatePosition(const std::string& symbol) {
     _impl->updatePosition(symbol);
}

void CtpTradeProvider::sendOrder(const FreeQuant::Order& o) {
    _impl->sendOrder(o);
}

void CtpTradeProvider::cancelOrder(const FreeQuant::Order& o) {
    _impl->cancelOrder(o);
}

void CtpTradeProvider::replaceOrder(const FreeQuant::Order& o) {
    _impl->replaceOrder(o);
}

void CtpTradeProvider::openOrders() const {
    _impl->openOrders();
}


void CtpTradeProvider::updateIntrument(const std::string& symbol, bool block) {
    _impl->updateIntrument(symbol, block);
}

} // namespace FreeQuant
