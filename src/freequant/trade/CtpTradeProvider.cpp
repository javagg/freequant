#include <algorithm>
#include <iostream>

#include <freequant/strategy/Order.h>
#include <freequant/strategy/Position.h>
#include <freequant/strategy/Instrument.h>

#include "CtpTradeProvider.h"
#include "api/trade/win/public/ThostFtdcTraderApi.h"


using namespace std;

namespace FreeQuant {

static long requestId = 0;

class CtpTradeProvider::Impl {
public:
    Impl(FreeQuant::TradeProvider::Callback *callback) : _callback(callback), _api(0) {

    }

    ~Impl() {

    }

    void connect() {}
    void disconnect() {}
    bool isConnected() const {}

    void logon() {
        CThostFtdcReqUserLoginField req = {};
        _appId.copy(req.BrokerID, _appId.size());
        _userId.copy(req.UserID, _userId.size());
        _password.copy(req.Password, _password.size());
        int ret = _api->ReqUserLogin(&req, ++requestId);
    }

    void logout() {
        CThostFtdcUserLogoutField req = {};
        _appId.copy(req.BrokerID, _appId.size());
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

    void subscribe(std::vector<std::string> symbols) {

    }

    void unsubscribe(std::vector<std::string> symbols) {

    }

    virtual void sendOrder(FreeQuant::Order& o)  {
        CThostFtdcInputOrderField field = {};
        _appId.copy(field.BrokerID, _appId.size());
        _userId.copy(field.InvestorID, _userId.size());
        o.instrument.copy(field.InstrumentID, o.instrument.size());
    //    o.instrumentId.copy(field.OrderRef, o.instrumentId.size());

    //    o.instrumentId.copy(field.UserID, o.instrumentId.size());

    //    o.instrumentId.copy(field.OrderPriceType, o.size());
    //    o.instrumentId.copy(field.Direction, o.instrumentId.size());
    //    o.instrumentId.copy(field.CombOffsetFlag, o.instrumentId.size());
        field.LimitPrice = o.limitPrice();
        field.VolumeTotalOriginal = o.qty();
        field.TimeCondition = THOST_FTDC_TC_IOC;

        std::string GTDDate = "20121111";

        GTDDate.copy(field.GTDDate, GTDDate.size());
        field.VolumeCondition = THOST_FTDC_VC_AV;
        field.MinVolume = o.tickSize();
        field.ContingentCondition = THOST_FTDC_CC_Immediately;
        field.StopPrice = o.stopPrice();
        field.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
        field.IsAutoSuspend = true;
    //    field.BusinessUnit = '2';
        field.RequestID = requestId++;
        field.UserForceClose = true;

        _api->ReqOrderInsert(&field, requestId++);
    }

    virtual void cancelOrder(FreeQuant::Order& order) {
        CThostFtdcInputOrderActionField req = {};
        _appId.copy(req.BrokerID, _appId.size());
        _userId.copy(req.InvestorID, _userId.size());
        req.ActionFlag = THOST_FTDC_AF_Delete;

         int ret = _api->ReqOrderAction(&req, ++requestId);
    }

    virtual void replaceOrder(FreeQuant::Order& order) {
        CThostFtdcInputOrderActionField req = {};
        _appId.copy(req.BrokerID, _appId.size());
        _userId.copy(req.InvestorID, _userId.size());
        req.ActionFlag = THOST_FTDC_AF_Modify;

         int ret = _api->ReqOrderAction(&req, ++requestId);
    }

    void updateAccounts() {

    }

    void updatePosition(std::string symbol) {
        CThostFtdcQryInvestorPositionField req = {};
        _appId.copy(req.BrokerID, _appId.size());
        _userId.copy(req.InvestorID, _userId.size());
        symbol.copy(req.InstrumentID, symbol.size());
        int ret = _api->ReqQryInvestorPosition(&req, ++requestId);
    }

    void openOrders() const {

    }

    void updateIntrument(std::string symbol, bool block = false) {
        CThostFtdcQryInstrumentField field = {};
        string instrumentId = "";
        string exchangeId = "";
        string exchangeInstId = "";
        string productId = "";

        instrumentId.copy(field.InstrumentID, instrumentId.size());
        exchangeId.copy(field.ExchangeID, exchangeId.size());
        exchangeInstId.copy(field.ExchangeInstID, exchangeInstId.size());
        productId.copy(field.ProductID, productId.size());

        _api->ReqQryInstrument(&field, requestId++);
    }

    CThostFtdcTraderApi *_api;

    void OnFrontConnected() {};
    void OnFrontDisconnected(int nReason) {}
    void OnHeartBeatWarning(int nTimeLapse) {}
    void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspUserLogin(CThostFtdcRspUserLoginField *rspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
            cout << rspUserLogin->SessionID << endl;
//            onLogon();
    }

    void OnRspUserLogout(CThostFtdcUserLogoutField *userLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
            cout << userLogout->UserID << endl;
//            onLogout();
    }

    void OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {

    }

    void OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {

    }

    void OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {

    }

    void OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {

    }

    void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {

    }

    void OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspQryInstrument(CThostFtdcInstrumentField *i, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        FreeQuant::Instrument instrument(i->InstrumentID);
        instrument.setExchange(i->ExchangeInstID);
        instrument.setName(i->InstrumentName);
        instrument.setExpireDate(FreeQuant::DateTime(i->ExpireDate));
        instrument.setMultipler(i->VolumeMultiple);
        instrument.setTickSize(i->PriceTick);
        instrument.setMargin(i->LongMarginRatio);
        instrument.setType(FreeQuant::Instrument::Stock);
    }

    void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    void OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    void OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspQryTransferSerial(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {

    }

    void OnRtnOrder(CThostFtdcOrderField *pOrder) {

    }

    void OnRtnTrade(CThostFtdcTradeField *pTrade) {

    }

    void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo) {};
    void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo) {};
    void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus) {};
    void OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo) {};
    void OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder) {};
    void OnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *pRspTransfer) {};
    void OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *pRspTransfer) {};
    void OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *pRspRepeal) {};
    void OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *pRspRepeal) {};
    void OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer) {};
    void OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer) {};
    void OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField *pRspRepeal) {};
    void OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField *pRspRepeal) {};
    void OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount) {};
    void OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) {};
    void OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) {};
    void OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) {};
    void OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) {};
    void OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo) {};
    void OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *pRspRepeal) {};
    void OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *pRspRepeal) {};
    void OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRtnOpenAccountByBank(CThostFtdcOpenAccountField *pOpenAccount) {};
    void OnRtnCancelAccountByBank(CThostFtdcCancelAccountField *pCancelAccount) {};
    void OnRtnChangeAccountByBank(CThostFtdcChangeAccountField *pChangeAccount) {};

private:
    FreeQuant::TradeProvider::Callback *_callback;
    std::string _appId;
    std::string _userId;
    std::string _password;
};

CtpTradeProvider::CtpTradeProvider(FreeQuant::TradeProvider::Callback *callback) : _impl(new CtpTradeProvider::Impl(callback)) {
}

CtpTradeProvider::~CtpTradeProvider() {
    delete _impl;
}

void CtpTradeProvider::connect() {
    _impl->connect();
}

void CtpTradeProvider::disconnect() {
    _impl->disconnect();
}

bool CtpTradeProvider::isConnected() const {
    return _impl->isConnected();
}

void CtpTradeProvider::logon() {
    _impl->logon();
}


void CtpTradeProvider::logout() {
    _impl->logout();
}

void CtpTradeProvider::subscribe(std::vector<std::string> symbols) {

}

void CtpTradeProvider::unsubscribe(std::vector<std::string> symbols) {

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

void CtpTradeProvider::updatePosition(string symbol) {
     _impl->updatePosition(symbol);
}

void CtpTradeProvider::sendOrder(FreeQuant::Order& o) {
    _impl->sendOrder(o);
}

void CtpTradeProvider::cancelOrder(FreeQuant::Order& o) {
    _impl->cancelOrder(o);
}

void CtpTradeProvider::replaceOrder(FreeQuant::Order& o) {
    _impl->replaceOrder(o);
}

void CtpTradeProvider::updateIntrument(std::string symbol, bool block) {
    _impl->updateIntrument(symbol, block);
}

} // namespace FreeQuant
