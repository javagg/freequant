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
    Impl(FreeQuant::MarketDataProvider::Callback *callback = 0) :
        _callback(callback), _api(0), _connected(false) {}

    virtual ~Impl() {
        disconnect();
    }

    void setCallback(FreeQuant::MarketDataProvider::Callback *callback) {
        _callback = callback;
    }

    virtual void connect(bool block = true) {
        string connection = "protocal=tcp;ip=asp-sim2-front1.financial-trading-platform.com;port=26213;userid=888888;password=888888;brokerid=4070";
        if (_api == 0) {
            _front = "tcp://asp-sim2-front1.financial-trading-platform.com:26213";
            _userId = "888888";
            _password = "888888";;
            _brokerId = "4070";

            _api = CThostFtdcMdApi::CreateFtdcMdApi("");
            _api->RegisterSpi(this);
            _api->RegisterFront(const_cast<char *>(_front.c_str()));
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

    FreeQuant::MarketDataProvider::Callback *_callback;

    boost::mutex _mutex;
    boost::condition_variable _condition;
    std::string _front;
    std::string _userId;
    std::string _password;
    std::string _brokerId;

    CThostFtdcMdApi *_api;
    bool _connected;

    void OnFrontConnected() {
        cerr << "--->>> " << __FUNCTION__ <<  endl;

        CThostFtdcReqUserLoginField req = {};
        _brokerId.copy(req.BrokerID, _brokerId.size());
        _userId.copy(req.UserID, _userId.size());
        _password.copy(req.Password, _password.size());
        int ret = _api->ReqUserLogin(&req, ++requestId);
        cerr << "--->>>>>> call ReqUserLogin " << ((ret==0) ? "success" : "failed") << endl;
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
            if (_callback) _callback->onConnected();

            boost::unique_lock<boost::mutex> lock(_mutex);
            _condition.notify_one();
         }
    }

    void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        cerr << "--->>> " << __FUNCTION__ << endl;
    }

    void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        cout << __FUNCTION__ << endl;
    }

    void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *specificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
            cerr << __FUNCTION__ << endl;
            cerr << "subscribe " <<  specificInstrument->InstrumentID << endl;
    }

    void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *specificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        cerr << __FUNCTION__ << endl;
        cerr << "unsubscribe " << specificInstrument->InstrumentID << endl;
    }

    void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *depthMarketData) {
        cerr << __FUNCTION__ << endl;
        boost::gregorian::date d = boost::gregorian::from_undelimited_string(depthMarketData->TradingDay);
        string sdate = to_iso_extended_string(d);
        string str = boost::str(boost::format("%s %s.%s") % sdate %
            depthMarketData->UpdateTime % depthMarketData->UpdateMillisec);
        boost::posix_time::ptime dt = boost::posix_time::time_from_string(str);
        Bar bar(depthMarketData->OpenPrice, depthMarketData->HighestPrice, depthMarketData->LowestPrice,
            depthMarketData->ClosePrice, depthMarketData->Volume);
        if (_callback) _callback->onBar(bar);

//         Bar bar(depthMarketData->LastPrice, depthMarketData->HighestPrice, depthMarketData->LowestPrice, depthMarketData->LastPrice);
//         _onBar(bar);

//        TThostFtdcDateType	TradingDay;
//        ///合约代码
//        TThostFtdcInstrumentIDType	InstrumentID;
//        ///交易所代码
//        TThostFtdcExchangeIDType	ExchangeID;
//        ///合约在交易所的代码
//        TThostFtdcExchangeInstIDType	ExchangeInstID;
//        ///最新价
//        TThostFtdcPriceType	LastPrice;
//        ///上次结算价
//        TThostFtdcPriceType	PreSettlementPrice;
//        ///昨收盘
//        TThostFtdcPriceType	PreClosePrice;
//        ///昨持仓量
//        TThostFtdcLargeVolumeType	PreOpenInterest;
//        ///今开盘
//        TThostFtdcPriceType	OpenPrice;
//        ///最高价
//        TThostFtdcPriceType	HighestPrice;
//        ///最低价
//        TThostFtdcPriceType	LowestPrice;
//        ///数量
//        TThostFtdcVolumeType	Volume;
//        ///成交金额
//        TThostFtdcMoneyType	Turnover;
//        ///持仓量
//        TThostFtdcLargeVolumeType	OpenInterest;
//        ///今收盘
//        TThostFtdcPriceType	ClosePrice;
//        ///本次结算价
//        TThostFtdcPriceType	SettlementPrice;
//        ///涨停板价
//        TThostFtdcPriceType	UpperLimitPrice;
//        ///跌停板价
//        TThostFtdcPriceType	LowerLimitPrice;
//        ///昨虚实度
//        TThostFtdcRatioType	PreDelta;
//        ///今虚实度
//        TThostFtdcRatioType	CurrDelta;
//        ///最后修改时间
//        TThostFtdcTimeType	UpdateTime;
//        ///最后修改毫秒
//        TThostFtdcMillisecType	UpdateMillisec;
//        ///申买价一
//        TThostFtdcPriceType	BidPrice1;
//        ///申买量一
//        TThostFtdcVolumeType	BidVolume1;
//        ///申卖价一
//        TThostFtdcPriceType	AskPrice1;
//        ///申卖量一
//        TThostFtdcVolumeType	AskVolume1;
//        ///申买价二
//        TThostFtdcPriceType	BidPrice2;
//        ///申买量二
//        TThostFtdcVolumeType	BidVolume2;
//        ///申卖价二
//        TThostFtdcPriceType	AskPrice2;
//        ///申卖量二
//        TThostFtdcVolumeType	AskVolume2;
//        ///申买价三
//        TThostFtdcPriceType	BidPrice3;
//        ///申买量三
//        TThostFtdcVolumeType	BidVolume3;
//        ///申卖价三
//        TThostFtdcPriceType	AskPrice3;
//        ///申卖量三
//        TThostFtdcVolumeType	AskVolume3;
//        ///申买价四
//        TThostFtdcPriceType	BidPrice4;
//        ///申买量四
//        TThostFtdcVolumeType	BidVolume4;
//        ///申卖价四
//        TThostFtdcPriceType	AskPrice4;
//        ///申卖量四
//        TThostFtdcVolumeType	AskVolume4;
//        ///申买价五
//        TThostFtdcPriceType	BidPrice5;
//        ///申买量五
//        TThostFtdcVolumeType	BidVolume5;
//        ///申卖价五
//        TThostFtdcPriceType	AskPrice5;
//        ///申卖量五
//        TThostFtdcVolumeType	AskVolume5;
//        ///当日均价
//        TThostFtdcPriceType	AveragePrice;
    }

    bool errorOccurred(CThostFtdcRspInfoField *rspInfo) {
        bool occurred = rspInfo && rspInfo->ErrorID != 0;
        if (occurred) {
            cerr << "--->>> ErrorID=" << rspInfo->ErrorID << ", ErrorMsg=" << rspInfo->ErrorMsg << endl;
        }
        return (rspInfo && rspInfo->ErrorID != 0);
    }
};

CtpMarketDataProvider::CtpMarketDataProvider(FreeQuant::MarketDataProvider::Callback *callback) :
    _impl(new CtpMarketDataProvider::Impl(callback)) {
}

CtpMarketDataProvider::~CtpMarketDataProvider() {
    delete _impl;
    _impl = 0;
}

void CtpMarketDataProvider::setCallback(FreeQuant::MarketDataProvider::Callback *callback) {
    _impl->setCallback(callback);
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

void CtpMarketDataProvider::subscribe(const Symbols& symbols) {
    _impl->subscribe(symbols);
}

void CtpMarketDataProvider::unsubscribe(const Symbols& symbols) {
    _impl->unsubscribe(symbols);
}

} // namespace FreeQuant

