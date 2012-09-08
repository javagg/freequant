
#include <cstring>
#include <iostream>
#include <vector>

#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>

#include "ctpprovider.h"
#include "api/trade/win/public/ThostFtdcMdApi.h"

using namespace std;

namespace FreeQuant { namespace MarketData {

static int requestId = 0;

class MdSpi : public CThostFtdcMdSpi {
public:
    MdSpi() {
              cout << "ok" << endl;
        char *mdFront = "tcp://asp-sim1-front1.financial-trading-platform.com:41213";
        api = CThostFtdcMdApi::CreateFtdcMdApi();
        api->RegisterSpi(this);
        api->RegisterFront(mdFront);
        api->Init();

    }

    ~MdSpi() {
        api->Release();
    }

    virtual void OnRspError(CThostFtdcRspInfoField *rspInfo, int requestId, bool last) {

    }

    virtual void OnFrontDisconnected(int reason) {

    }

    virtual void OnHeartBeatWarning(int timeLapse) {

    }

    virtual void OnFrontConnected() {

    }

    virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *rspUserLogin,	CThostFtdcRspInfoField *rspInfo, int requestId, bool last) {
        boost::unique_lock<boost::mutex> lock(mutex);
        condition.notify_all();
    }

    virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *specificInstrument, CThostFtdcRspInfoField *rspInfo, int requestId, bool last) {

    }

    virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *specificInstrument, CThostFtdcRspInfoField *rspInfo, int requestId, bool last) {

    }

    virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *depthMarketData) {

    }

    void connect() {
        CThostFtdcReqUserLoginField req = {};
    //    memset(&req, 0, sizeof(req));

        string appId = "2030";
        appId.copy(req.BrokerID, appId.size());
        string userId = "0000000624";
        userId.copy(req.UserID, userId.size());
        string passwd = "asdfgh";
        passwd.copy(req.Password, passwd.size());
    //    strcpy(req.BrokerID, appId);
    //    strcpy(req.UserID, userId);
    //    strcpy(req.Password, passwd);
        cout << req.BrokerID  << endl;
//        int ret = api->ReqUserLogin(&req, ++requestId);
    //    int ret = pUserApi->ReqUserLogin(&req, ++requestId);

//        cerr<<"  | ͵¼..."<<((ret == 0) ? "ɹ" :"ʧ") << endl;

//      boost::unique_lock<boost::mutex> lock(mutex);
//      condition.wait(mutex);

//      vector<string> instruments;
//      char *instrs[1];
//      api->SubscribeMarketData(instrs, instruments.size());

    }
    CThostFtdcMdApi *api;
private:
    boost::condition condition;
    boost::mutex mutex;
};

//void CtpMdSpi::OnRspError(CThostFtdcRspInfoField *rspInfo, int requestID, bool last) {
//    IsErrorRspInfo(rspInfo);
//}

//void CtpMdSpi::OnFrontDisconnected(int reason) {
//  cerr<<" Ӧ | ж..."
//    << " reason=" << reason << endl;
//}

//void CtpMdSpi::OnHeartBeatWarning(int nTimeLapse)
//{
//  cerr<<" Ӧ | ʱ..."
//    << " TimerLapse = " << nTimeLapse << endl;
//}

//void CtpMdSpi::OnFrontConnected()
//{
//    cerr<<" ӽǰ...ɹ"<<endl;
//}

//void CtpMdSpi::ReqUserLogin(TThostFtdcBrokerIDType	appId,
//            TThostFtdcUserIDType	userId,	TThostFtdcPasswordType	passwd)
//{
//    CThostFtdcReqUserLoginField req;
//    memset(&req, 0, sizeof(req));
//    strcpy(req.BrokerID, appId);
//    strcpy(req.UserID, userId);
//    strcpy(req.Password, passwd);
//    int ret = userApi->ReqUserLogin(&req, ++requestId);
//  cerr<<"  | ͵¼..."<<((ret == 0) ? "ɹ" :"ʧ") << endl;
////  SetEvent(g_hEvent);
//}

//void CtpMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
//        CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
//{
//    if (!IsErrorRspInfo(pRspInfo) && pRspUserLogin)
//    {
//    cerr<<" Ӧ | ¼ɹ...ǰ:"
//      <<pRspUserLogin->TradingDay<<endl;
//    }
////  if(bIsLast) SetEvent(g_hEvent);
//}

//void CtpMdSpi::SubscribeMarketData(char* instIdList)
//{
//  vector<char*> list;
//  char *token = strtok(instIdList, ",");
//  while( token != NULL ){
//    list.push_back(token);
//    token = strtok(NULL, ",");
//  }
//  unsigned int len = list.size();
//  char** pInstId = new char* [len];
//  for(unsigned int i=0; i<len;i++)  pInstId[i]=list[i];
//    int ret=userApi->SubscribeMarketData(pInstId, len);
//  cerr<<"  | 鶩... "<<((ret == 0) ? "ɹ" : "ʧ")<< endl;
////  SetEvent(g_hEvent);
//}

//void CtpMdSpi::OnRspSubMarketData(
//         CThostFtdcSpecificInstrumentField *pSpecificInstrument,
//         CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
//{
//    cerr<<" Ӧ |  鶩...ɹ"<<endl;
////  if(bIsLast)  SetEvent(g_hEvent);
//}

//void CtpMdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument,
//             CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
//{
//    cerr<<" Ӧ |  ȡ...ɹ"<<endl;
////  if(bIsLast)  SetEvent(g_hEvent);
//}

//void CtpMdSpi::OnRtnDepthMarketData(
//             CThostFtdcDepthMarketDataField *pDepthMarketData)
//{
//  cerr<<"  | Լ:"<<pDepthMarketData->InstrumentID
//    <<" ּ:"<<pDepthMarketData->LastPrice
//    <<" ߼:" << pDepthMarketData->HighestPrice
//    <<" ͼ:" << pDepthMarketData->LowestPrice
//    <<" һ:" << pDepthMarketData->AskPrice1
//    <<" һ:" << pDepthMarketData->AskVolume1
//    <<" һ:" << pDepthMarketData->BidPrice1
//    <<" һ:" << pDepthMarketData->BidVolume1
//    <<" ֲ:"<< pDepthMarketData->OpenInterest <<endl;
//}

//bool CtpMdSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
//{
//  bool ret = ((pRspInfo) && (pRspInfo->ErrorID != 0));
//  if (ret){
//    cerr<<" Ӧ | "<<pRspInfo->ErrorMsg<<endl;
//  }
//  return ret;
//}

CtpProvider::CtpProvider() : spi(new MdSpi()) {
}

CtpProvider::~CtpProvider() {
    delete spi;
}

void CtpProvider::connect() {
    spi->connect();
}

void CtpProvider::disconnect() {
//    spi->disconnect();
//     char *instuments[100];
//    userApi->UnSubscribeMarketData(instuments, 1);
}

bool CtpProvider::isConnected() const {
    return true;
}

}}

