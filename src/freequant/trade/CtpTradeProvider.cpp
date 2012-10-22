#include <algorithm>
#include <iostream>

#include <freequant/strategy/Order.h>
#include <freequant/strategy/Position.h>
#include <freequant/strategy/Instrument.h>

#include "api/trade/win/public/ThostFtdcTraderApi.h"
#include "CtpTradeProvider.h"

using namespace std;

namespace FreeQuant {

static long requestId = 0;

CtpTradeProvider::CtpTradeProvider() {
}

CtpTradeProvider::~CtpTradeProvider() {
}

void CtpTradeProvider::connect() {
//    spi->connect();
}

void CtpTradeProvider::disconnect() {
//    spi->disconnect();
}

bool CtpTradeProvider::isConnected() const {
    return true;
}

void CtpTradeProvider::logon() {
    CThostFtdcReqUserLoginField req = {};
    _appId.copy(req.BrokerID, _appId.size());
    _userId.copy(req.UserID, _userId.size());
    _password.copy(req.Password, _password.size());
    int ret = _api->ReqUserLogin(&req, ++requestId);
}

void CtpTradeProvider::OnRspUserLogin(CThostFtdcRspUserLoginField *rspUserLogin, CThostFtdcRspInfoField *rspInfo, int requestID, bool last) {
    cout << rspUserLogin->SessionID << endl;
    onLogon();
}

void CtpTradeProvider::logout() {
    CThostFtdcUserLogoutField req = {};
    _appId.copy(req.BrokerID, _appId.size());
    _userId.copy(req.UserID, _userId.size());
    int ret = _api->ReqUserLogout(&req, ++requestId);
}

void CtpTradeProvider::OnRspUserLogout(CThostFtdcUserLogoutField *userLogout, CThostFtdcRspInfoField *rspInfo, int requestID, bool last) {
    cout << userLogout->UserID << endl;
    onLogout();
}

void CtpTradeProvider::OnRspQryTradingAccount(CThostFtdcTradingAccountField *tradingAccount, CThostFtdcRspInfoField *rspInfo, int requestID, bool last) {

}

void CtpTradeProvider::OnRspOrderInsert(CThostFtdcInputOrderField *inputOrder, CThostFtdcRspInfoField *rspInfo, int requestID, bool last) {
  cerr<< inputOrder->OrderRef<<endl;
}

void CtpTradeProvider::OnRspOrderAction(CThostFtdcInputOrderActionField *inputOrderAction, CThostFtdcRspInfoField *rspInfo, int requestID, bool last) {
      cerr << "ExchangeID:" <<inputOrderAction->ExchangeID
        <<" OrderSysID:"<<inputOrderAction->OrderSysID<<endl;
}

void CtpTradeProvider::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *position, CThostFtdcRspInfoField *rspInfo, int requestID, bool last) {
    FreeQuant::Position pos;
    cerr << position->InstrumentID
         << position->PosiDirection
         << position->PositionDate
         << position->Position
         << position->OpenVolume
    << position->CloseVolume
    << position->OpenAmount
    << position->CloseAmount
    << endl;
}

void CtpTradeProvider::OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *investorPositionDetail,
        CThostFtdcRspInfoField *rspInfo, int requestID, bool last) {
}

void CtpTradeProvider::OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *positionDetail,
        CThostFtdcRspInfoField *rspInfo, int requestID, bool last) {

}

void CtpTradeProvider::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {

}



void CtpTradeProvider::OnRtnOrder(CThostFtdcOrderField *order) {
      cerr<<"InstrumentID:"<< order->InstrumentID

        <<"LimitPrice:"<<order->LimitPrice
        <<" VolumeTotalOriginal:"<<order->VolumeTotalOriginal
        <<" BrokerOrderSeq:"<<order->BrokerOrderSeq
        <<"OrderSysID:"<<order->OrderSysID
        <<"StatusMsg:"<<order->StatusMsg<<endl;
}

void CtpTradeProvider::OnRspError(CThostFtdcRspInfoField *rspInfo, int requestID, bool last) {

}

void CtpTradeProvider::OnRtnTrade(CThostFtdcTradeField *trade) {
    cerr<<"InstrumentID:"<< trade->InstrumentID
       <<" Price:"<<trade->Price
       <<" Volume:"<<trade->Volume
       <<" OrderSysID:"<<trade->OrderSysID
       <<" TradeID:"<<trade->TradeID<<endl;
}

vector<string> CtpTradeProvider::availableExchanges() const {
    string exchangeId = "dsf";
    CThostFtdcQryExchangeField field = {};
    exchangeId.copy(field.ExchangeID, exchangeId.size());
    _api->ReqQryExchange(&field, ++requestId);

    return vector<string>();
}

vector<string> CtpTradeProvider::availableInstruments() const {
    CThostFtdcQryInstrumentField field;
//    api->ReqQryInstrument()
    return vector<string>();
}

void CtpTradeProvider::updateAccounts() {
    CThostFtdcQryTradingAccountField req = {};
    _appId.copy(req.BrokerID, _appId.size());
    _userId.copy(req.InvestorID, _userId.size());
    int ret = _api->ReqQryTradingAccount(&req, ++requestId);
 }

void CtpTradeProvider::updatePositions() {

}

void CtpTradeProvider::updatePosition(string symbol) {
    CThostFtdcQryInvestorPositionField req = {};
    _appId.copy(req.BrokerID, _appId.size());
    _userId.copy(req.InvestorID, _userId.size());
    symbol.copy(req.InstrumentID, symbol.size());
    int ret = _api->ReqQryInvestorPosition(&req, ++requestId);
}

void CtpTradeProvider::sendOrder(FreeQuant::Order& o) {

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

void CtpTradeProvider::cancelOrder(FreeQuant::Order& o) {
    CThostFtdcInputOrderActionField req = {};
    _appId.copy(req.BrokerID, _appId.size());
    _userId.copy(req.InvestorID, _userId.size());
    req.ActionFlag = THOST_FTDC_AF_Delete;

     int ret = _api->ReqOrderAction(&req, ++requestId);

}

void CtpTradeProvider::replaceOrder(FreeQuant::Order& o) {
    CThostFtdcInputOrderActionField req = {};
    _appId.copy(req.BrokerID, _appId.size());
    _userId.copy(req.InvestorID, _userId.size());
    req.ActionFlag = THOST_FTDC_AF_Modify;

     int ret = _api->ReqOrderAction(&req, ++requestId);

}

void CtpTradeProvider::updateIntrument(std::string symbol, bool block) {
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

void CtpTradeProvider::OnRspQryInstrument(CThostFtdcInstrumentField *i, CThostFtdcRspInfoField *rspInfo, int nequestID, bool last) {
    FreeQuant::Instrument instrument(i->InstrumentID);
    instrument.setExchange(i->ExchangeInstID);
    instrument.setName(i->InstrumentName);
    instrument.setExpireDate(FreeQuant::DateTime(i->ExpireDate));
    instrument.setMultipler(i->VolumeMultiple);
    instrument.setTickSize(i->PriceTick);
    instrument.setMargin(i->LongMarginRatio);
    instrument.setType(FreeQuant::Instrument::Stock);


}

} // namespace FreeQuant
