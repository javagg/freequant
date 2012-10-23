#include <cstring>
#include <iostream>
#include <vector>

#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/date_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/format.hpp>

#include <freequant/marketdata/Bar.h>

#include "CtpMarketDataProvider.h"
#include "api/trade/win/public/ThostFtdcMdApi.h"

using namespace std;

namespace FreeQuant {

static int requestId = 0;

class CtpMarketDataProvider::Impl : private CThostFtdcMdSpi {
public:
    explicit Impl() : _api(0), _connected(false) {}
    virtual ~Impl() {
        disconnect();
    }
    virtual void connect(bool block = true) {
        string connection = "protocal=tcp;ip=asp-sim2-front1.financial-trading-platform.com;port=26213;userid=888888;password=888888;brokerid=4070";
        if (_api == 0) {
            char *front = "tcp://asp-sim2-front1.financial-trading-platform.com:26213";
            TThostFtdcBrokerIDType brokerId = "4070";
            TThostFtdcInvestorIDType userId = "888888";
            TThostFtdcPasswordType password = "888888";

            _api = CThostFtdcMdApi::CreateFtdcMdApi("");
            _api->RegisterSpi(this);
            _api->RegisterFront(front);
            _api->Init();
        }
        boost::unique_lock<boost::mutex> l(_mutex);
        _condition.wait(l);
    }

    virtual void disconnect(bool block = true) {
        if (_api != 0) {
            _api->RegisterSpi(0);
            _api->Release();
            _api = 0;
        }
    }


    virtual bool isConnected() const {
        return _connected;
    }

    virtual void subscribe(std::vector<std::string> symbols) {
        vector<const char *> items(symbols.size());
        transform(symbols.begin(), symbols.end(), items.begin(), mem_fun_ref(&string::c_str));
        _api->SubscribeMarketData(const_cast<char**>(&items[0]), items.size());
    }

    virtual void unsubscribe(std::vector<std::string> symbols) {
        vector<const char *> items(symbols.size());
        transform(symbols.begin(), symbols.end(), items.begin(), mem_fun_ref(&string::c_str));
        _api->UnSubscribeMarketData(const_cast<char**>(&items[0]), items.size());
    }

    boost::mutex _mutex;
    boost::condition_variable _condition;

    CThostFtdcMdApi *_api;
    bool _connected;
    void OnFrontConnected() {
        cerr << "--->>> " << __FUNCTION__ <<  endl;

        string appId = "2030";
        string userId = "00092";
        string passwd = "888888";

        CThostFtdcReqUserLoginField req = {};
        appId.copy(req.BrokerID, appId.size());
        userId.copy(req.UserID, userId.size());
        passwd.copy(req.Password, passwd.size());
        int ret = _api->ReqUserLogin(&req, ++requestId);
        cerr << "--->>>>>>>>>> call ReqUserLogin " << ((ret==0) ? "success" : "failed") << endl;
    }

    void OnFrontDisconnected(int nReason) {

    }

    void OnHeartBeatWarning(int timeLapse) {
        cerr << "OnHeartBeatWarning..." << timeLapse << endl;
    }

    void OnRspUserLogin(CThostFtdcRspUserLoginField *rspUserLogin, CThostFtdcRspInfoField *rspInfo, int requestID, bool last) {
        cerr << "--->>> " << __FUNCTION__ << endl;
        if (!errorOccurred(rspInfo) && last) {
            cerr << "--->>> TradingDay " << _api->GetTradingDay() << endl;
            _connected = true;

//            onConnected();
            boost::unique_lock<boost::mutex> lock(_mutex);
            _condition.notify_one();
         }
    }

    void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {

    }

    void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        cout << __FUNCTION__ << endl;
    }

    void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *specificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
            cout << __FUNCTION__ << endl;
            cout << "subscribe " <<  specificInstrument->InstrumentID << endl;
    }

    void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *specificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        cout << __FUNCTION__ << endl;
        cout << "unsubscribe " << specificInstrument->InstrumentID << endl;
    }

    void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *depthMarketData) {
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
//         Bar bar(depthMarketData->LastPrice, depthMarketData->HighestPrice, depthMarketData->LowestPrice, depthMarketData->LastPrice);
//         _onBar(bar);
    }

    bool errorOccurred(CThostFtdcRspInfoField *rspInfo) {
        bool occurred = rspInfo && rspInfo->ErrorID != 0;
        if (occurred) {
            cerr << "--->>> ErrorID=" << rspInfo->ErrorID << ", ErrorMsg=" << rspInfo->ErrorMsg << endl;
        }
        return (rspInfo && rspInfo->ErrorID != 0);
    }
};

CtpMarketDataProvider::CtpMarketDataProvider() :
    _impl(new CtpMarketDataProvider::Impl()) {
}

CtpMarketDataProvider::~CtpMarketDataProvider() {
    delete _impl;
    _impl = 0;
}

void CtpMarketDataProvider::connect(bool block) {
    _impl->connect(block);
}

void CtpMarketDataProvider::disconnect(bool block) {
    _impl->disconnect(block);
}

bool CtpMarketDataProvider::isConnected() const {
    return _impl->isConnected();
}

void CtpMarketDataProvider::subscribe(std::vector<std::string> symbols) {
    _impl->subscribe(symbols);
}

void CtpMarketDataProvider::unsubscribe(std::vector<std::string> symbols) {
    _impl->unsubscribe(symbols);
}

} // namespace FreeQuant

