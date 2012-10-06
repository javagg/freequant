#include <iostream>

#include "api/trade/win/public/ThostFtdcTraderApi.h"
#include "ctptradeprovider.h"

using namespace std;

namespace FreeQuant { namespace Trade {

class TraderSpi : public CThostFtdcTraderSpi {
public:
    TraderSpi() : api(0) {
    }

    ~TraderSpi() {
        disconnect();
    }

    void connect() {
        if (api == 0) {
            char *front = "tcp://asp-sim2-front1.financial-trading-platform.com:26213";
            TThostFtdcBrokerIDType brokerId = "4070";
            TThostFtdcInvestorIDType userId = "888888";
            TThostFtdcPasswordType password = "888888";

            api = CThostFtdcTraderApi::CreateFtdcTraderApi("");
            api->RegisterSpi(this);
            api->SubscribePublicTopic(THOST_TERT_RESTART);
            api->SubscribePrivateTopic(THOST_TERT_RESTART);
            api->RegisterFront(front);
            api->Init();

            cout << "connect..." << endl;
//            api->Join();
        }
    }

    void disconnect() {
        if (api != 0) {
            api->RegisterSpi(0);
            api->Release();
            api = 0;
        }
    }

    bool isConnected() const {
        return true;
    }

    virtual void OnFrontConnected() {
        cerr << "OnFrontConnected" << endl;
    }

    virtual void OnFrontDisconnected(int reason) {
        cerr << "OnFrontDisconnected" << reason << endl;
    }
    virtual void OnHeartBeatWarning(int timeLapse) {
    }
    virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField *rspAuthenticateField, CThostFtdcRspInfoField *rspInfo, int requestID, bool lLast) {
    }
    virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ǳӦ
    virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ûӦ
    virtual void OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ʽ˻Ӧ
    virtual void OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///¼Ӧ
    virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///Ԥ¼Ӧ
    virtual void OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///Ԥ񳷵¼Ӧ
    virtual void OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///Ӧ
    virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ѯ󱨵Ӧ
    virtual void OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///Ͷ߽ȷӦ
    virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ɾԤӦ
    virtual void OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ɾԤ񳷵Ӧ
    virtual void OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ѯӦ
    virtual void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ѯɽӦ
    virtual void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ѯͶֲ߳Ӧ
    virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ѯʽ˻Ӧ
    virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ѯͶӦ
    virtual void OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ѯױӦ
    virtual void OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ѯԼ֤Ӧ
    virtual void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ѯԼӦ
    virtual void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ѯӦ
    virtual void OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ѯԼӦ
    virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ѯӦ
    virtual void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ѯͶ߽Ӧ
    virtual void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ѯתӦ
    virtual void OnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ѯͶֲ߳ϸӦ
    virtual void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ѯͻ֪ͨӦ
    virtual void OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ѯϢȷӦ
    virtual void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ѯͶֲ߳ϸӦ
    virtual void OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ѯ֤ϵͳ͹˾ʽ˻ԿӦ
    virtual void OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ѯֵ۵ϢӦ
    virtual void OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ѯתˮӦ
    virtual void OnRspQryTransferSerial(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ѯǩԼϵӦ
    virtual void OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///Ӧ
    virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///֪ͨ
    virtual void OnRtnOrder(CThostFtdcOrderField *pOrder) {};

    ///ɽ֪ͨ
    virtual void OnRtnTrade(CThostFtdcTradeField *pTrade) {};

    ///¼ر
    virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo) {};

    ///ر
    virtual void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo) {};

    ///Լ״̬֪ͨ
    virtual void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus) {};

    ///֪ͨ
    virtual void OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo) {};

    ///ʾУ
    virtual void OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder) {};

    ///ѯǩԼӦ
    virtual void OnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ѯԤӦ
    virtual void OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ѯԤ񳷵Ӧ
    virtual void OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ѯ֪ͨӦ
    virtual void OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ѯ͹˾ײӦ
    virtual void OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ѯ͹˾㷨Ӧ
    virtual void OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///зʽתڻ֪ͨ
    virtual void OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *pRspTransfer) {};

    ///зڻʽת֪ͨ
    virtual void OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *pRspTransfer) {};

    ///зתڻ֪ͨ
    virtual void OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *pRspRepeal) {};

    ///зڻת֪ͨ
    virtual void OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *pRspRepeal) {};

    ///ڻʽתڻ֪ͨ
    virtual void OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer) {};

    ///ڻڻʽת֪ͨ
    virtual void OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer) {};

    ///ϵͳʱڻֹתڻдϺ̷ص֪ͨ
    virtual void OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField *pRspRepeal) {};

    ///ϵͳʱڻֹڻתдϺ̷ص֪ͨ
    virtual void OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField *pRspRepeal) {};

    ///ڻѯ֪ͨ
    virtual void OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount) {};

    ///ڻʽתڻر
    virtual void OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) {};

    ///ڻڻʽתдر
    virtual void OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) {};

    ///ϵͳʱڻֹתڻر
    virtual void OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) {};

    ///ϵͳʱڻֹڻתдر
    virtual void OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) {};

    ///ڻѯر
    virtual void OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo) {};

    ///ڻתڻдϺ̷ص֪ͨ
    virtual void OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *pRspRepeal) {};

    ///ڻڻתдϺ̷ص֪ͨ
    virtual void OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *pRspRepeal) {};

    ///ڻʽתڻӦ
    virtual void OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ڻڻʽתӦ
    virtual void OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///ڻѯӦ
    virtual void OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///зڿ֪ͨ
    virtual void OnRtnOpenAccountByBank(CThostFtdcOpenAccountField *pOpenAccount) {};

    ///з֪ͨ
    virtual void OnRtnCancelAccountByBank(CThostFtdcCancelAccountField *pCancelAccount) {};

    ///з˺֪ͨ
    virtual void OnRtnChangeAccountByBank(CThostFtdcChangeAccountField *pChangeAccount) {};
private:
    CThostFtdcTraderApi *api;
};

CtpTradeProvider::CtpTradeProvider() : spi(new TraderSpi()) {
}

CtpTradeProvider::~CtpTradeProvider() {
    delete spi;
}

void CtpTradeProvider::connect() {
//    spi->connect();
}

void CtpTradeProvider::disconnect() {
//    spi->disconnect();
}

bool CtpTradeProvider::isConnected() const {
//    return spi->isConnected();
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

void CtpTradeProvider::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *investorPosition, CThostFtdcRspInfoField *rspInfo, int requestID, bool last) {

}
void CtpTradeProvider::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {

}

void CtpTradeProvider::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {

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

void CtpTradeProvider::reqOrderInsert(TThostFtdcInstrumentIDType instId, TThostFtdcDirectionType dir, TThostFtdcCombOffsetFlagType kpp,
    TThostFtdcPriceType price, TThostFtdcVolumeType vol) {
    CThostFtdcInputOrderField req = {};
//    memset(&req, 0, sizeof(req));
//    strcpy(req.BrokerID, appId);  //ÓŠÓÃµ¥ÔªŽúÂë
//    strcpy(req.InvestorID, userId); //Í¶×ÊÕßŽúÂë
//    strcpy(req.InstrumentID, instId); //ºÏÔŒŽúÂë
//    strcpy(req.OrderRef, orderRef);  //±šµ¥ÒýÓÃ
//  int nextOrderRef = atoi(orderRef);
//  sprintf(orderRef, "%d", ++nextOrderRef);

    req.OrderPriceType = THOST_FTDC_OPT_LimitPrice;//ŒÛžñÀàÐÍ=ÏÞŒÛ
//    req.Direction = MapDirection(dir,true);  //ÂòÂô·œÏò
//    req.CombOffsetFlag[0] = MapOffset(kpp[0],true); //THOST_FTDC_OF_Open; //×éºÏ¿ªÆœ±êÖŸ:¿ª²Ö
    req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;	  //×éºÏÍ¶»úÌ×±£±êÖŸ
    req.LimitPrice = price;	//ŒÛžñ
    req.VolumeTotalOriginal = vol;	///ÊýÁ¿
    req.TimeCondition = THOST_FTDC_TC_GFD;  //ÓÐÐ§ÆÚÀàÐÍ:µ±ÈÕÓÐÐ§
    req.VolumeCondition = THOST_FTDC_VC_AV; //³Éœ»Á¿ÀàÐÍ:ÈÎºÎÊýÁ¿
    req.MinVolume = 1;	//×îÐ¡³Éœ»Á¿:1
    req.ContingentCondition = THOST_FTDC_CC_Immediately;  //Ž¥·¢ÌõŒþ:Á¢ŒŽ

  //TThostFtdcPriceType	StopPrice;  //Ö¹ËðŒÛ
    req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;	//Ç¿ÆœÔ­Òò:·ÇÇ¿Æœ
    req.IsAutoSuspend = 0;  //×Ô¶¯¹ÒÆð±êÖŸ:·ñ
    req.UserForceClose = 0;   //ÓÃ»§Ç¿ÆÀ±êÖŸ:·ñ

    int ret = api->ReqOrderInsert(&req, 1);
    cerr<<" ÇëÇó | ·¢ËÍ±šµ¥..."<<((ret == 0)?"³É¹Š":"Ê§°Ü")<< endl;
}

void CtpTradeProvider::reqOrderAction(TThostFtdcSequenceNoType orderSeq) {
//  bool found=false; unsigned int i=0;
//  for(i=0;i<orderList.size();i++){
//    if(orderList[i]->BrokerOrderSeq == orderSeq){ found = true; break;}
//  }
//  if(!found){cerr<<" ÇëÇó | ±šµ¥²»ŽæÔÚ."<<endl; return;}

    CThostFtdcInputOrderActionField req = {};

//    strcpy(req.BrokerID, appId);   //Ÿ­ŒÍ¹«ËŸŽúÂë
//    strcpy(req.InvestorID, userId); //Í¶×ÊÕßŽúÂë
    //strcpy(req.OrderRef, pOrderRef); //±šµ¥ÒýÓÃ
    //req.FrontID = frontId;           //Ç°ÖÃ±àºÅ
    //req.SessionID = sessionId;       //»á»°±àºÅ
//  strcpy(req.ExchangeID, orderList[i]->ExchangeID);
//  strcpy(req.OrderSysID, orderList[i]->OrderSysID);
//    req.ActionFlag = THOST_FTDC_AF_Delete;  //²Ù×÷±êÖŸ

    int ret = api->ReqOrderAction(&req, 22);
    cerr<< " ÇëÇó | ·¢ËÍ³·µ¥..." <<((ret == 0)?"³É¹Š":"Ê§°Ü") << endl;
}

void CtpTradeProvider::reqQryInvestorPosition(TThostFtdcInstrumentIDType instId) {
    CThostFtdcQryInvestorPositionField req = {};
//    strcpy(req.BrokerID, appId);
//    strcpy(req.InvestorID, userId);
//    strcpy(req.InstrumentID, instId);
    int ret = api->ReqQryInvestorPosition(&req, 1);
    cerr<<" ÇëÇó | ·¢ËÍ³Ö²Ö²éÑ¯..."<<((ret == 0)?"³É¹Š":"Ê§°Ü")<<endl;
}

void CtpTradeProvider::reqQryTradingAccount() {
    CThostFtdcQryTradingAccountField req = {};

//    strcpy(req.BrokerID, appId);
//    strcpy(req.InvestorID, userId);
//    int ret = pUserApi->ReqQryTradingAccount(&req, ++requestId);
//    cerr<<" ÇëÇó | ·¢ËÍ×Êœð²éÑ¯..."<<((ret == 0)?"³É¹Š":"Ê§°Ü")<<endl;

}

void CtpTradeProvider::reqUserLogin(TThostFtdcBrokerIDType	vAppId, TThostFtdcUserIDType	vUserId,	TThostFtdcPasswordType	vPasswd)
{

    CThostFtdcReqUserLoginField req;
//    memset(&req, 0, sizeof(req));
//    strcpy(req.BrokerID, vAppId); strcpy(appId, vAppId);
//    strcpy(req.UserID, vUserId);  strcpy(userId, vUserId);
//    strcpy(req.Password, vPasswd);
//    int ret = pUserApi->ReqUserLogin(&req, ++requestId);
//  cerr<<" ÇëÇó | ·¢ËÍµÇÂŒ..."<<((ret == 0) ? "³É¹Š" :"Ê§°Ü") << endl;
}

//void CtpTradeProvider::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
//		CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
//{
//	if ( !IsErrorRspInfo(pRspInfo) && pRspUserLogin ) {
//    // ±£Žæ»á»°²ÎÊý
//		frontId = pRspUserLogin->FrontID;
//		sessionId = pRspUserLogin->SessionID;
//		int nextOrderRef = atoi(pRspUserLogin->MaxOrderRef);
//		sprintf(orderRef, "%d", ++nextOrderRef);
//    cerr<<" ÏìÓŠ | µÇÂŒ³É¹Š...µ±Ç°œ»Ò×ÈÕ:"
//      <<pRspUserLogin->TradingDay<<endl;
//  }
//  if(bIsLast) SetEvent(g_hEvent);
//}

void CtpTradeProvider::reqSettlementInfoConfirm() {
    CThostFtdcSettlementInfoConfirmField req;
//    memset(&req, 0, sizeof(req));
//    strcpy(req.BrokerID, appId);
//    strcpy(req.InvestorID, userId);
//    int ret = pUserApi->ReqSettlementInfoConfirm(&req, ++requestId);
//    cerr<<" ÇëÇó | ·¢ËÍœáËãµ¥È·ÈÏ..."<<((ret == 0)?"³É¹Š":"Ê§°Ü")<<endl;
}

}}
