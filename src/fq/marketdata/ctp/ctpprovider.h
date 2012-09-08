#ifndef FQ_MARKETDATA_CTP_CTPPROVIDER_H
#define FQ_MARKETDATA_CTP_CTPPROVIDER_H

#include <fq/marketdata/provider.h>
#include "api/trade/win/public/ThostFtdcMdApi.h"

namespace FreeQuant { namespace MarketData {

//class CtpMdSpi : public CThostFtdc CThostFtdcMdApi *userApi;MdSpi {
//public:
//    CtpMdSpi(CThostFtdcMdApi *api) : userApi(api) {}
//    virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestId, bool bIsLast);
//    virtual void OnFrontDisconnected(int reason);
//    virtual void OnHeartBeatWarning(int timeLapsed);
//    virtual void OnFrontConnected();
//    virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *rspUserLogin,	CThostFtdcRspInfoField *rspInfo, int requestId, bool last);
//    virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *specificInstrument, CThostFtdcRspInfoField *rspInfo, int requestId, bool last);
//    virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *specificInstrument, CThostFtdcRspInfoField *rspInfo, int requestId, bool last);
//    virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *depthMarketData);

//public:
//    void ReqUserLogin(TThostFtdcBrokerIDType appId, TThostFtdcUserIDType userId, TThostFtdcPasswordType	passwd);
//    void SubscribeMarketData(char *instIdList);
//    bool IsErrorRspInfo(CThostFtdcRspInfoField *rspInfo);

//private:
//    CThostFtdcMdApi *userApi;
//};

class MdSpi;

class CtpProvider : public Provider {
public:
    CtpProvider();
    virtual ~CtpProvider();
    virtual void connect();
    virtual void disconnect();
    virtual bool isConnected();
    std::string name() { return "CTP"; }

private:
    MdSpi *spi;
};

}}
#endif // FQ_MARKETDATA_CTP_CTPPROVIDER_H
