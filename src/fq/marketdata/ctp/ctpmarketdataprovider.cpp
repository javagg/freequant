#include <cstring>
#include <iostream>
#include <vector>

#include <boost/date_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/thread/condition_variable.hpp> // #include <condition_variable> // for c++11
#include <boost/thread/mutex.hpp> // #include <mutex> // for c++11
#include <boost/format.hpp>

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
       cerr << "OnHeartBeatWarning..." << timeLapse << endl;
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
            m_connected = true;
        }
    }

    virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *specificInstrument, CThostFtdcRspInfoField *rspInfo, int requestId, bool last) {
       cerr << __FUNCTION__ << endl;
       cout << specificInstrument->InstrumentID << endl;
    }

    virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *specificInstrument, CThostFtdcRspInfoField *rspInfo, int requestId, bool last) {
        cerr << __FUNCTION__ << endl;
        cout << specificInstrument->InstrumentID << endl;
    }

    virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *depthMarketData) {
        boost::gregorian::date d = boost::gregorian::from_undelimited_string(depthMarketData->TradingDay);
        string sdate = to_iso_extended_string(d);
        string str = boost::str(boost::format("%s %s.%s") % sdate %
            depthMarketData->UpdateTime % depthMarketData->UpdateMillisec);
        boost::posix_time::ptime dt = boost::posix_time::time_from_string(str);

        cerr<<" mardate | symbol:"<<depthMarketData->InstrumentID
              << "timestamp: " << str
              << " " << dt
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
        string connection = "protocal=tcp;ip=asp-sim2-front1.financial-trading-platform.com;port=26213;userid=888888;password=888888;brokerid=4070";
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
        api->SubscribeMarketData(const_cast<char**>(&items[0]), items.size());
    }

    void unsubscribe(std::vector<std::string> symbols) {
        vector<const char *> items(symbols.size());
        transform(symbols.begin(), symbols.end(), items.begin(), mem_fun_ref(&string::c_str));
        api->UnSubscribeMarketData(const_cast<char**>(&items[0]), items.size());
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

void CtpMarketDataProvider::onConnected() {

}

void CtpMarketDataProvider::onDisconnected() {

}

}}

