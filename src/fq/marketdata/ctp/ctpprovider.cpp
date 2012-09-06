
#include <cstring>

#include <iostream>
#include <vector>

#include "ctpprovider.h"

using namespace std;

namespace FreeQuant { namespace MarketData {

static int requestId = 0;

void CtpMdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo,
        int nRequestID, bool bIsLast)
{
  IsErrorRspInfo(pRspInfo);
}

void CtpMdSpi::OnFrontDisconnected(int nReason)
{
  cerr<<" 响应 | 连接中断..."
    << " reason=" << nReason << endl;
}

void CtpMdSpi::OnHeartBeatWarning(int nTimeLapse)
{
  cerr<<" 响应 | 心跳超时警告..."
    << " TimerLapse = " << nTimeLapse << endl;
}

void CtpMdSpi::OnFrontConnected()
{
    cerr<<" 连接交易前置...成功"<<endl;
}

void CtpMdSpi::ReqUserLogin(TThostFtdcBrokerIDType	appId,
            TThostFtdcUserIDType	userId,	TThostFtdcPasswordType	passwd)
{
    CThostFtdcReqUserLoginField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.BrokerID, appId);
    strcpy(req.UserID, userId);
    strcpy(req.Password, passwd);
    int ret = pUserApi->ReqUserLogin(&req, ++requestId);
  cerr<<" 请求 | 发送登录..."<<((ret == 0) ? "成功" :"失败") << endl;
//  SetEvent(g_hEvent);
}

void CtpMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
        CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (!IsErrorRspInfo(pRspInfo) && pRspUserLogin)
    {
    cerr<<" 响应 | 登录成功...当前交易日:"
      <<pRspUserLogin->TradingDay<<endl;
    }
//  if(bIsLast) SetEvent(g_hEvent);
}

void CtpMdSpi::SubscribeMarketData(char* instIdList)
{
  vector<char*> list;
  char *token = strtok(instIdList, ",");
  while( token != NULL ){
    list.push_back(token);
    token = strtok(NULL, ",");
  }
  unsigned int len = list.size();
  char** pInstId = new char* [len];
  for(unsigned int i=0; i<len;i++)  pInstId[i]=list[i];
    int ret=pUserApi->SubscribeMarketData(pInstId, len);
  cerr<<" 请求 | 发送行情订阅... "<<((ret == 0) ? "成功" : "失败")<< endl;
//  SetEvent(g_hEvent);
}

void CtpMdSpi::OnRspSubMarketData(
         CThostFtdcSpecificInstrumentField *pSpecificInstrument,
         CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    cerr<<" 响应 |  行情订阅...成功"<<endl;
//  if(bIsLast)  SetEvent(g_hEvent);
}

void CtpMdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument,
             CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    cerr<<" 响应 |  行情取消订阅...成功"<<endl;
//  if(bIsLast)  SetEvent(g_hEvent);
}

void CtpMdSpi::OnRtnDepthMarketData(
             CThostFtdcDepthMarketDataField *pDepthMarketData)
{
  cerr<<" 行情 | 合约:"<<pDepthMarketData->InstrumentID
    <<" 现价:"<<pDepthMarketData->LastPrice
    <<" 最高价:" << pDepthMarketData->HighestPrice
    <<" 最低价:" << pDepthMarketData->LowestPrice
    <<" 卖一价:" << pDepthMarketData->AskPrice1
    <<" 卖一量:" << pDepthMarketData->AskVolume1
    <<" 买一价:" << pDepthMarketData->BidPrice1
    <<" 买一量:" << pDepthMarketData->BidVolume1
    <<" 持仓量:"<< pDepthMarketData->OpenInterest <<endl;
}

bool CtpMdSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
  bool ret = ((pRspInfo) && (pRspInfo->ErrorID != 0));
  if (ret){
    cerr<<" 响应 | "<<pRspInfo->ErrorMsg<<endl;
  }
  return ret;
}

CtpProvider::CtpProvider() {

}

}}

