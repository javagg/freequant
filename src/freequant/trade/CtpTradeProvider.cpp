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
    cerr<<" 请求 | 发送登录..."<<((ret == 0) ? "成功" :"失败") << endl;
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
    cerr<<" 请求 | 发送登录..."<<((ret == 0) ? "成功" :"失败") << endl;
}

void CtpTradeProvider::OnRspUserLogout(CThostFtdcUserLogoutField *userLogout, CThostFtdcRspInfoField *rspInfo, int requestID, bool last) {
    cout << userLogout->UserID << endl;
    onLogout();
}

void CtpTradeProvider::OnRspQryTradingAccount(CThostFtdcTradingAccountField *tradingAccount, CThostFtdcRspInfoField *rspInfo, int requestID, bool last) {

}

void CtpTradeProvider::OnRspOrderInsert(CThostFtdcInputOrderField *inputOrder, CThostFtdcRspInfoField *rspInfo, int requestID, bool last) {
  cerr<<"ÏìÓŠ | ±šµ¥Ìáœ»³É¹Š...±šµ¥ÒýÓÃ:"<<inputOrder->OrderRef<<endl;
}

void CtpTradeProvider::OnRspOrderAction(CThostFtdcInputOrderActionField *inputOrderAction, CThostFtdcRspInfoField *rspInfo, int requestID, bool last) {
      cerr<< " ÏìÓŠ | ³·µ¥³É¹Š..."
        << "œ»Ò×Ëù:"<<inputOrderAction->ExchangeID
        <<" ±šµ¥±àºÅ:"<<inputOrderAction->OrderSysID<<endl;
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
      cerr<<" ±šµ¥ | ºÏÔŒ:"<< order->InstrumentID
//        <<" ·œÏò:"<< MapDirection(order->Direction,false)
//        <<" ¿ªÆœ:"<< MapOffset(order->CombOffsetFlag[0],false)
        <<" ŒÛžñ:"<<order->LimitPrice
        <<" ÊýÁ¿:"<<order->VolumeTotalOriginal
        <<" ÐòºÅ:"<<order->BrokerOrderSeq
        <<" ±šµ¥±àºÅ:"<<order->OrderSysID
        <<" ×ŽÌ¬:"<<order->StatusMsg<<endl;
}

void CtpTradeProvider::OnRspError(CThostFtdcRspInfoField *rspInfo, int requestID, bool last) {
    cerr<<" ÏìÓŠ | "<<rspInfo->ErrorMsg<<endl;
}

void CtpTradeProvider::OnRtnTrade(CThostFtdcTradeField *trade) {
    cerr<<" ³Éœ» | ºÏÔŒ:"<< trade->InstrumentID
//       <<" ·œÏò:"<<MapDirection(pTrade->Direction,false)
//       <<" ¿ªÆœ:"<<MapOffset(pTrade->OffsetFlag,false)
       <<" ŒÛžñ:"<<trade->Price
       <<" ÊýÁ¿:"<<trade->Volume
       <<" ±šµ¥±àºÅ:"<<trade->OrderSysID
       <<" ³Éœ»±àºÅ:"<<trade->TradeID<<endl;
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
    cerr<<" 请求 | 发送资金查询..."<<((ret == 0)?"成功":"失败")<<endl;
}

void CtpTradeProvider::updatePositions() {

}

void CtpTradeProvider::updatePosition(string symbol) {
    CThostFtdcQryInvestorPositionField req = {};
    _appId.copy(req.BrokerID, _appId.size());
    _userId.copy(req.InvestorID, _userId.size());
    symbol.copy(req.InstrumentID, symbol.size());
    int ret = _api->ReqQryInvestorPosition(&req, ++requestId);
    cerr<<" 请求 | 发送持仓查询..."<<((ret == 0)?"成功":"失败")<<endl;
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
       //strcpy(req.OrderRef, pOrderRef); //报单引用
       //req.FrontID = frontId;           //前置编号
       //req.SessionID = sessionId;       //会话编号
//     strcpy(req.ExchangeID, orderList[i]->ExchangeID);
//     strcpy(req.OrderSysID, orderList[i]->OrderSysID);
     int ret = _api->ReqOrderAction(&req, ++requestId);
      cerr<< " 请求 | 发送撤单..." <<((ret == 0)?"成功":"失败") << endl;
}

void CtpTradeProvider::replaceOrder(FreeQuant::Order& o) {
    CThostFtdcInputOrderActionField req = {};
    _appId.copy(req.BrokerID, _appId.size());
    _userId.copy(req.InvestorID, _userId.size());
    req.ActionFlag = THOST_FTDC_AF_Modify;
       //strcpy(req.OrderRef, pOrderRef); //报单引用
       //req.FrontID = frontId;           //前置编号
       //req.SessionID = sessionId;       //会话编号
//     strcpy(req.ExchangeID, orderList[i]->ExchangeID);
//     strcpy(req.OrderSysID, orderList[i]->OrderSysID);
     int ret = _api->ReqOrderAction(&req, ++requestId);
      cerr<< " 请求 | 发送撤单..." <<((ret == 0)?"成功":"失败") << endl;
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
//    ///市价单最大下单量
//    TThostFtdcVolumeType	MaxMarketOrderVolume;
//    ///市价单最小下单量
//    TThostFtdcVolumeType	MinMarketOrderVolume;
//    ///限价单最大下单量
//    TThostFtdcVolumeType	MaxLimitOrderVolume;
//    ///限价单最小下单量
//    TThostFtdcVolumeType	MinLimitOrderVolume;
//    ///合约数量乘数
//    ///创建日
//    TThostFtdcDateType	CreateDate;
//    ///上市日
//    TThostFtdcDateType	OpenDate;
//    ///到期日
//    TThostFtdcDateType	ExpireDate;
//    ///开始交割日
//    TThostFtdcDateType	StartDelivDate;
//    ///结束交割日
//    TThostFtdcDateType	EndDelivDate;
    ///合约生命周期状态
//    TThostFtdcInstLifePhaseType	InstLifePhase;
//    ///当前是否交易
//    TThostFtdcBoolType	IsTrading;
//    ///持仓类型
//    TThostFtdcPositionTypeType	PositionType;
//    ///持仓日期类型
//    TThostFtdcPositionDateTypeType	PositionDateType;
//    ///多头保证金率
//    TThostFtdcRatioType	LongMarginRatio;
//    ///空头保证金率
//    TThostFtdcRatioType	ShortMarginRatio;

}

} // namespace FreeQuant
