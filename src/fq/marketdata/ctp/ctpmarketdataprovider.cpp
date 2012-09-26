#include <cstring>
#include <iostream>
#include <vector>

#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>

#include <fq/marketdata/bar.h>

#include "ctpmarketdataprovider.h"
#include "api/trade/win/public/ThostFtdcMdApi.h"

using namespace std;

namespace FreeQuant { namespace MarketData {

static int requestId = 0;

class MdSpi : public CThostFtdcMdSpi {
public:
    MdSpi() : api(0), m_connected(false) {}

    ~MdSpi() {
        disconnect();
    }

    virtual void OnRspError(CThostFtdcRspInfoField *rspInfo, int requestId, bool last) {
        cout << "RspError" << endl;
    }

    virtual void OnFrontDisconnected(int reason) {

    }

    virtual void OnHeartBeatWarning(int timeLapse) {

    }

    virtual void OnFrontConnected() {
        cerr << "--->>> " << __FUNCTION__ << endl;

        string appId = "2030";
        string userId = "00092";
        string passwd = "888888";

        CThostFtdcReqUserLoginField req = {};
        appId.copy(req.BrokerID, appId.size());
        userId.copy(req.UserID, userId.size());
        passwd.copy(req.Password, passwd.size());
        int ret = api->ReqUserLogin(&req, ++requestId);
        cerr << "--->>> call ReqUserLogin " << ((ret==0) ? "success" : "failed") << endl;
    }

    virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *rspUserLogin,	CThostFtdcRspInfoField *rspInfo, int requestId, bool last) {
        cerr << "--->>> " << __FUNCTION__ << endl;
        if (!errorOccurred(rspInfo) && last) {
            cerr << "--->>> TradingDay " << api->GetTradingDay() << endl;
//            vector<char *> instruments;
//            instruments.push_back("IF1209");
//            instruments.push_back("cu0909");
//            int ret = api->SubscribeMarketData(&instruments[0], instruments.size());
//            cerr << "--->>> Subscribe MarketData " << ((ret == 0) ? "success" : "failed") << endl;
        }
    }

    virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *specificInstrument, CThostFtdcRspInfoField *rspInfo, int requestId, bool last) {
       cerr << __FUNCTION__ << endl;
       cout << specificInstrument->InstrumentID << endl;
    }

    virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *specificInstrument, CThostFtdcRspInfoField *rspInfo, int requestId, bool last) {

    }

    virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *depthMarketData) {
        cerr<<" mardate | symbol:"<<depthMarketData->InstrumentID
          <<" lastprice:"<<depthMarketData->LastPrice
          <<" high:" << depthMarketData->HighestPrice
          <<" low:" << depthMarketData->LowestPrice
          <<" ask1:" << depthMarketData->AskPrice1
          <<" asksize1:" << depthMarketData->AskVolume1
          <<" bid1:" << depthMarketData->BidPrice1
          <<" bidsize1:" << depthMarketData->BidVolume1
          <<" openinterest:"<< depthMarketData->OpenInterest <<endl;
//        Bar bar;
//        onBar(bar);
    }

    void connect() {
       if (api == 0) {
            char *front = "tcp://asp-sim2-front1.financial-trading-platform.com:26213";
            TThostFtdcBrokerIDType brokerId = "4070";
            TThostFtdcInvestorIDType userId = "888888";
            TThostFtdcPasswordType password = "888888";

            api = CThostFtdcMdApi::CreateFtdcMdApi("");
            api->RegisterSpi(this);
            api->RegisterFront(front);
            api->Init();
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
        return m_connected;
    }

    void subscribe(std::vector<std::string> symbols) {
        vector<const char *> items(symbols.size());
        transform(symbols.begin(), symbols.end(), items.begin(), mem_fun_ref(&string::c_str));
//        api->SubscribeMarketData(&items[0], items.size());
    }

    void unsubscribe(std::vector<std::string> symbols) {
        vector<const char *> items(symbols.size());
        transform(symbols.begin(), symbols.end(), items.begin(), mem_fun_ref(&string::c_str));
//        api->UnSubscribeMarketData(&items[0], items.size());
    }

    CThostFtdcMdApi *api;
private:
    bool m_connected;
    boost::condition_variable condition;
    boost::mutex mutex;

    bool errorOccurred(CThostFtdcRspInfoField *rspInfo) {
        bool occurred = rspInfo && rspInfo->ErrorID != 0;
        if (occurred) {
            cerr << "--->>> ErrorID=" << rspInfo->ErrorID << ", ErrorMsg=" << rspInfo->ErrorMsg << endl;
        }
        return (rspInfo && rspInfo->ErrorID != 0);
    }
};

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

CtpMarketDataProvider::CtpMarketDataProvider() : spi(new MdSpi()) {
}

CtpMarketDataProvider::~CtpMarketDataProvider() {
    delete spi;
}

void CtpMarketDataProvider::connect() {
    spi->connect();
}

void CtpMarketDataProvider::disconnect() {
    spi->disconnect();
}

bool CtpMarketDataProvider::isConnected() const {
    return spi->isConnected();
}

void CtpMarketDataProvider::subscribe(std::vector<std::string> symbols) {
    spi->subscribe(symbols);
}

void CtpMarketDataProvider::unsubscribe(std::vector<std::string> symbols) {
    spi->unsubscribe(symbols);
}

}}

