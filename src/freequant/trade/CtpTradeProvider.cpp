#include <algorithm>
#include <iostream>

#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

#include <freequant/marketdata/Bar.h>
#include <freequant/marketdata/Trade.h>
#include <freequant/strategy/Order.h>
#include <freequant/strategy/Position.h>
#include <freequant/strategy/Instrument.h>
#include <freequant/utils/Utility.h>
#include <freequant/Exception.h>

#include "CtpTradeProvider.h"
#include "ThostFtdcTraderApi.h"

using namespace std;

namespace FreeQuant {

static TThostFtdcOrderRefType orderRef = {};
static long requestId = 0;
static const char *flowPath = "fqctptrader";

class CtpTradeProvider::StructConvertor {
public:
    static inline void convert(const Order& order, CThostFtdcOrderField& field) {
        order.symbol().copy(field.InstrumentID, order.symbol().size());
//        order.type()
    }

    static inline void convert(const CThostFtdcOrderField& field, Order& order) {

    }
};

class CtpTradeProvider::FieldConvertor {
public:
    static inline void convert(TThostFtdcDirectionType from, Order::Side to) {
        switch (from) {
        case THOST_FTDC_D_Buy:
            to = Order::Buy; break;
        case THOST_FTDC_D_Sell:
            to = Order::Sell; break;
        default:break;
        }
    }
};

class CtpTradeProvider::Impl : public CThostFtdcTraderSpi {
public:
    typedef std::vector<Trade> Trades;
    typedef std::vector<Order> Orders;

    static const int reqTimeout;
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
        _api = CThostFtdcTraderApi::CreateFtdcTraderApi("Trade");
        _api->RegisterSpi(this);
        _api->RegisterFront(const_cast<char*>(_front.c_str()));
        _api->SubscribePrivateTopic(THOST_TERT_QUICK);
        _api->SubscribePrivateTopic(THOST_TERT_QUICK);
        _api->Init();

        if (block) {
            {
                boost::unique_lock<boost::mutex> lock(_mutex);
                while (!isConnected()) {
                    if (_condition.wait_for(lock, boost::chrono::seconds(reqTimeout))
                        == boost::cv_status::timeout) {
                        throw Timeout("CtpTradeProvider Connection Timeout");

//                        return;
                    }
                    CThostFtdcSettlementInfoConfirmField field = {};
                    _brokerId.copy(field.BrokerID, _brokerId.size());
                    _userId.copy(field.InvestorID, _userId.size());

                    cout << "ReqSettlementInfoConfirm...";
                    _api->ReqSettlementInfoConfirm(&field, ++requestId);

                    _condition.wait_for(lock, boost::chrono::seconds(reqTimeout));
                }
            }

            {
                boost::unique_lock<boost::mutex> lock(_mutex);
                CThostFtdcQryTradingAccountField field = {};
                _brokerId.copy(field.BrokerID, _brokerId.size());
                _userId.copy(field.InvestorID, _userId.size());
                _api->ReqQryTradingAccount(&field, ++requestId);
                _condition.wait_for(lock, boost::chrono::seconds(reqTimeout));
            }
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
        string exchanges[] = { "CFFEX", "SHFE", "CZCE", "DCE" };
        vector<string> ex(exchanges, exchanges+4);
        for (auto i = ex.begin(); i != ex.end(); ++i) {
            queryExchange(*i);
        }
        return ex;
    }

    std::vector<std::string> availableInstruments() const {
        CThostFtdcQryInstrumentField field = {};
//        _brokerId.copy(req.BrokerID, _brokerId.size());
//        _userId.copy(req.UserID, _userId.size());

//        CThostFtdcQryInstrumentField field = {};
//        symbol.copy(field.InstrumentID, symbol.size());
        _api->ReqQryInstrument(&field, requestId++);
        return vector<string>();
    }

    void queryExchange(const std::string& exchangeId) const {
        CThostFtdcQryExchangeField field = {};
        exchangeId.copy(field.ExchangeID, exchangeId.size());
        _api->ReqQryExchange(&field, ++requestId);

        boost::unique_lock<boost::mutex> lock(_mutex);
        _condition.wait_for(lock, boost::chrono::seconds(reqTimeout));
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
        field.IsAutoSuspend = 0;
        field.UserForceClose = true;
        int ret = _api->ReqOrderInsert(&field, requestId++);
    }

    void cancelOrder(const FreeQuant::Order& order) {
        CThostFtdcInputOrderActionField field = {};
        _brokerId.copy(field.BrokerID, _brokerId.size());
        _userId.copy(field.InvestorID, _userId.size());

//        _frontId.copy(field.FrontID, _frontId.size());
        field.FrontID = _frontId;
        field.SessionID = _sessionId;
//        _sessionId.copy(field.SessionID, _sessionId.size());
         strcpy(field.OrderRef, "4");
        ///
//        TThostFtdcOrderActionRefType	OrderActionRef;
        ///
//        TThostFtdcOrderRefType	OrderRef;
        ///
//        TThostFtdcRequestIDType	RequestID;
        ///ǰñ
//        TThostFtdcFrontIDType	FrontID;
        ///Ự
//        TThostFtdcSessionIDType	SessionID;
        ///
//        TThostFtdcExchangeIDType	ExchangeID;
        ///
//        TThostFtdcOrderSysIDType	OrderSysID;
        ///־
//        TThostFtdcActionFlagType	ActionFlag;
        ///۸
//        TThostFtdcPriceType	LimitPrice;
        ///仯
//        TThostFtdcVolumeType	VolumeChange;
        ///û
//        TThostFtdcUserIDType	UserID;
        ///Լ

        strcpy(field.OrderSysID, "86029");
//        order.orderId().copy(field.OrderSysID, order.orderId().size());
        field.ActionFlag = THOST_FTDC_AF_Delete;
        strcpy(field.InstrumentID, "IF1212");
//        order.symbol().copy(field.InstrumentID, order.symbol().size());
        int ret = _api->ReqOrderAction(&field, ++requestId);
    }

    void replaceOrder(const FreeQuant::Order& order) {
        CThostFtdcInputOrderActionField req = {};
        _brokerId.copy(req.BrokerID, _brokerId.size());
        _userId.copy(req.InvestorID, _userId.size());
        req.ActionFlag = THOST_FTDC_AF_Modify;

         int ret = _api->ReqOrderAction(&req, ++requestId);
    }

    void updateAccounts() {
        CThostFtdcQryInvestorField field = {};
        _brokerId.copy(field.BrokerID, _brokerId.size());
        _userId.copy(field.InvestorID, _userId.size());
        _api->ReqQryInvestor(&field, ++requestId);
    }

    void updatePosition(const std::string& symbol) {
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

    void fetchOrders(const std::string& symbol, const FreeQuant::DateTime& start, const FreeQuant::DateTime& end) {
        CThostFtdcQryOrderField field = {};
        _brokerId.copy(field.BrokerID, _brokerId.size());
        _userId.copy(field.InvestorID, _userId.size());
        symbol.copy(field.InstrumentID, symbol.size());

        _api->ReqQryOrder(&field, ++requestId);
    }

    void fetchTrades(const std::string& symbol, const FreeQuant::DateTime& start, const FreeQuant::DateTime& end) {
        CThostFtdcQryTradeField field = {};
        _brokerId.copy(field.BrokerID, _brokerId.size());
        _userId.copy(field.InvestorID, _userId.size());
        symbol.copy(field.InstrumentID, symbol.size());
        _api->ReqQryTrade(&field, ++requestId);
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
            _condition.notify_one();
        }
    }

    void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *confirm,
        CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        cout << "done" << endl;
        boost::unique_lock<boost::mutex> lock(_mutex);
        _condition.notify_all();
    }

    void OnRspQryInvestor(CThostFtdcInvestorField *i, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        std::cout << __FUNCTION__ << std::endl;
        if (!errorOccurred(pRspInfo)) {
             cout << "IdentifiedCardNo: " << i->IdentifiedCardNo  << endl
               << "OpenDate: " << i->OpenDate  << endl
                   ;
            if (bIsLast) {

            }
        }
    }

    void OnRspUserLogout(CThostFtdcUserLogoutField *userLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        cout << userLogout->UserID << endl;
         if (!errorOccurred(pRspInfo) && bIsLast) {
            boost::unique_lock<boost::mutex> lock(_mutex);
            _condition.notify_one();
         }
    }

    void OnRspQryExchange(CThostFtdcExchangeField *exchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        std::cout << __FUNCTION__ << std::endl;
        if (!errorOccurred(pRspInfo)) {
            std::cout << "ExchangeID: " << exchange->ExchangeID  << std::endl
                     << "ExchangeName: " << exchange->ExchangeName  << std::endl
                      << "ExchangeProperty: " << exchange->ExchangeProperty << std::endl
                         ;
            if (bIsLast) {
                cout << "done................................." << endl;
                boost::unique_lock<boost::mutex> lock(_mutex);
                _condition.notify_one();
            }
        }
    }

    void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        std::cout << __FUNCTION__ << std::endl;
        if (!errorOccurred(pRspInfo)) {
            cout << " ................................." << endl;
            CThostFtdcInvestorPositionField p = *pInvestorPosition;
            std::cout << "InstrumentID: " << p.InstrumentID  << std::endl
                 << "PosiDirection: " << p.PosiDirection << endl
                   << "Position: " << p.Position << endl
          << "PositionProfit: " << p.PositionProfit << endl
            << "Commission: " << p.Commission << endl

                << "PreMargin: " << p.PreMargin << endl
                << "UseMargin: " << p.UseMargin << endl
                << "FrozenMargin: " << p.FrozenMargin << endl
                << "FrozenCash: " << p.FrozenCash << endl
                << "FrozenCommission: " << p.FrozenCommission << endl
                << "CashIn: " << p.CashIn << endl
                << "Commission: " << p.Commission << endl
                << "PositionDate: " << p.PositionDate << endl
                << "PositionCost: " << p.PositionCost << endl
            ;
              if (bIsLast) {
                  cout << "done................................." << endl;
              }
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

    void OnRspOrderAction(CThostFtdcInputOrderActionField *action, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        std::cout << __FUNCTION__ << std::endl;
         if (!errorOccurred(pRspInfo)) {

            if (bIsLast) {
                cout << "cancel order sent!" << endl;
            }
         }
    }

    void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        if (!errorOccurred(pRspInfo)) {
            CThostFtdcTradeField trade = *pTrade;
            cout << "....................................." << endl
                 << "TradeID:"<< trade.TradeID << endl
                   << "OrderRef:"<< trade.OrderRef << endl
                << "InstrumentID:"<< trade.InstrumentID << endl
                << "Direction:"<< trade.Direction << endl
                 << "OffsetFlag:"<< trade.OffsetFlag << endl
                 << "OffsetFlag:"<< trade.Price << endl
                 << "Volume:"<< trade.Volume << endl
                 << "TradeTime:"<< trade.TradeTime << endl
                 << "TradeType:"<< trade.TradeType << endl
                  ;
            if (bIsLast) {
                cout << "done................................." << endl;
            }
        }

    }

    void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        if (!errorOccurred(pRspInfo)) {
            CThostFtdcOrderField order = *pOrder;
            cout << "....................................." << endl
                 << "OrderRef:"<< order.OrderRef << endl
                   << "OrderSysID:"<< order.OrderSysID << endl
                << "InstrumentID:"<< order.InstrumentID << endl
                << "Direction:"<< order.Direction << endl
                << "OrderPriceType:"<< order.OrderPriceType << endl
                 << "LimitPrice:"<< order.LimitPrice << endl
                << "VolumeTotalOriginal:"<< order.VolumeTotalOriginal << endl
               << "VolumeCondition:"<< order.VolumeCondition << endl
                << "StopPrice:"<< order.StopPrice << endl
           << "RequestID:"<< order.RequestID << endl
             << "OrderSubmitStatus:"<< order.OrderSubmitStatus << endl
                 << "OrderStatus:"<< order.OrderStatus << endl
             << "OrderType:"<< order.OrderType << endl

             << "VolumeTraded:"<< order.VolumeTraded << endl
              << "VolumeTotal:"<< order.VolumeTotal << endl
              << "InsertTime:"<< order.InsertTime << endl
          << "CancelTime:"<< order.CancelTime << endl
            << "UpdateTime:"<< order.UpdateTime << endl
        << "SequenceNo:"<< order.SequenceNo << endl
            ;
            if (bIsLast) {
                cout << "done................................." << endl;
            }
        }
    }

    void OnRtnOrder(CThostFtdcOrderField *pOrder) {
        std::cout << __FUNCTION__ << std::endl;
        CThostFtdcOrderField order = *pOrder;

        cout << "BrokerOrderSeq:"<<order.BrokerOrderSeq<<endl
             << "OrderSysID:"<<order.OrderSysID<<endl
             << "OrderStatus:"<<order.OrderStatus<<endl
            << "OrderSubmitStatus:"<<order.OrderSubmitStatus<<endl
            << "InsertTime:"<<order.InsertTime<<endl
           << "ActiveTime:"<<order.ActiveTime<<endl
           << "SuspendTime:"<<order.SuspendTime<<endl
           << "UpdateTime:"<<order.UpdateTime<<endl
           << "CancelTime:"<<order.CancelTime<<endl
            ;
    }

    void OnRtnTrade(CThostFtdcTradeField *pTrade) {
        std::cout << __FUNCTION__ << std::endl;
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

    Orders orders;

    Trades trades;
    mutable boost::mutex _mutex;
    mutable boost::condition_variable _condition;
};

const int CtpTradeProvider::Impl::reqTimeout = 5;

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

void CtpTradeProvider::updateAccount(bool block) {
    _impl->updateAccounts();
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

void CtpTradeProvider::fetchOrders(const std::string& symbol, const DateTime& start, const DateTime& end) {
    _impl->fetchOrders(symbol, start, end);
}

void CtpTradeProvider::fetchTrades(const std::string& symbol, const DateTime& start, const DateTime& end) {
    _impl->fetchTrades(symbol, start, end);
}


} // namespace FreeQuant
