#include <cstring>
#include <iostream>
#include <vector>

#include <boost/signals2.hpp>

#include <boost/thread/barrier.hpp>

#include <boost/date_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/format.hpp>

#include <freequant/marketdata/Bar.h>
#include <freequant/utils/Utility.h>
#include <freequant/detail/Atomic.hpp>
#include <freequant/detail/Notifier.h>

#include "CtpMarketDataProvider.h"
#include "ThostFtdcMdApi.h"

using namespace std;

namespace FreeQuant {

static int requestId = 0;

using Detail::Atomic;
using Detail::Notifier;

class CtpMarketDataProvider::Impl : private CThostFtdcMdSpi {
public:
    typedef CThostFtdcMdSpi Spi;
    typedef CThostFtdcMdApi Api;

    Impl(const std::string& connection, FreeQuant::MarketDataProvider::Callback *callback = 0) :
        _callback(callback), _api(0), _connected(false) {
        auto params = FreeQuant::parseParamsFromString(connection);
        _front = params["protocal"] + "://" + params["host"] + ":"  + params["port"];
        _userId = params["userid"];
        _password = params["password"];
        _brokerId = params["brokerid"];
    }

    virtual ~Impl() {
        disconnect();
    }

    void setCallback(FreeQuant::MarketDataProvider::Callback *callback) {
        _callback = callback;
    }

    void connect(bool block = true) {
        if (_api == 0) {
            _api = CThostFtdcMdApi::CreateFtdcMdApi("");
            _api->RegisterSpi(this);
            _api->RegisterFront(const_cast<char *>(_front.c_str()));

            std::function<void()> func = [&]() { _api->Init(); };
            _notifier.call(func);
        }
    }

    void disconnect(bool block = true) {
        if (_api != 0) {
            _api->RegisterSpi(0);
            _api->Release();
            _api = 0;
        }
    }

    bool isConnected() const {
        return _connected;
    }

    void subscribe(std::vector<std::string> symbols) {
        vector<const char *> items(symbols.size());
        transform(symbols.begin(), symbols.end(), items.begin(), mem_fun_ref(&string::c_str));

        std::function<void()> func = [&]() {
            _api->SubscribeMarketData(const_cast<char**>(&items[0]), items.size());
        };
        _notifier.call(func);
    }

    void unsubscribe(std::vector<std::string> symbols) {
        vector<const char *> items(symbols.size());
        transform(symbols.begin(), symbols.end(), items.begin(), mem_fun_ref(&string::c_str));
        _api->UnSubscribeMarketData(const_cast<char**>(&items[0]), items.size());
    }

    FreeQuant::MarketDataProvider::Callback *_callback;

    std::string _front;
    std::string _userId;
    std::string _password;
    std::string _brokerId;

    Api *_api;

    Atomic<bool> __connected;
    boost::mutex _connected_mutex;
    bool _connected;

    Notifier _notifier;

    void OnFrontConnected() {
        cerr << "--->>> " << __FUNCTION__ <<  endl;

        CThostFtdcReqUserLoginField req = {};
        _brokerId.copy(req.BrokerID, _brokerId.size());
        _userId.copy(req.UserID, _userId.size());
        _password.copy(req.Password, _password.size());

        int ret = _api->ReqUserLogin(&req, ++requestId);
        cerr << "--->>>>>> call ReqUserLogin " << ((ret==0) ? "success" : "failed") << endl;
    }

    void OnFrontDisconnected(int reason) {  std::cout << "disconnected: " << reason << std::endl; }
    void OnHeartBeatWarning(int timeLapse) { std::cout << "heartbeat: " << timeLapse << std::endl; }

    void OnRspUserLogin(CThostFtdcRspUserLoginField *rspUserLogin, CThostFtdcRspInfoField *rspInfo, int requestID, bool last) {

        cerr << "--->>> " << __FUNCTION__ << endl;
        cerr << "--->>> " << "request id: " << requestID << endl;
        if (!errorOccurred(rspInfo) && last) {
            cerr << "--->>> TradingDay " << _api->GetTradingDay() << endl;
            _connected = true;
            __connected.set(true);

            if (_callback) _callback->onConnected();

            _notifier.complete();
         }
    }

    void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        cerr << "--->>> " << __FUNCTION__ << endl;
    }

    void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        cout << __FUNCTION__ << endl;
        if (bIsLast) {
            _notifier.complete(nRequestID);
        }
    }

    void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *specificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
            cerr << __FUNCTION__ << endl;
            cerr << "subscribe " <<  specificInstrument->InstrumentID << endl;
            if (!errorOccurred(pRspInfo)) {
                if (bIsLast) {
//                   _subscribe_barrier.wait();
                    _notifier.complete();
                }
            }

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

//        TThostFtdcInstrumentIDType	InstrumentID;

//        TThostFtdcExchangeIDType	ExchangeID;

//        TThostFtdcExchangeInstIDType	ExchangeInstID;

//        TThostFtdcPriceType	LastPrice;

//        TThostFtdcPriceType	PreSettlementPrice;

//        TThostFtdcPriceType	PreClosePrice;

//        TThostFtdcLargeVolumeType	PreOpenInterest;

//        TThostFtdcPriceType	OpenPrice;

//        TThostFtdcPriceType	HighestPrice;

//        TThostFtdcPriceType	LowestPrice;

//        TThostFtdcVolumeType	Volume;

//        TThostFtdcMoneyType	Turnover;

//        TThostFtdcLargeVolumeType	OpenInterest;

//        TThostFtdcPriceType	ClosePrice;

//        TThostFtdcPriceType	SettlementPrice;

//        TThostFtdcPriceType	UpperLimitPrice;

//        TThostFtdcPriceType	LowerLimitPrice;

//        TThostFtdcRatioType	PreDelta;

//        TThostFtdcRatioType	CurrDelta;

//        TThostFtdcTimeType	UpdateTime;

//        TThostFtdcMillisecType	UpdateMillisec;

//        TThostFtdcPriceType	BidPrice1;

//        TThostFtdcVolumeType	BidVolume1;

//        TThostFtdcPriceType	AskPrice1;

//        TThostFtdcVolumeType	AskVolume1;

//        TThostFtdcPriceType	BidPrice2;

//        TThostFtdcVolumeType	BidVolume2;

//        TThostFtdcPriceType	AskPrice2;

//        TThostFtdcVolumeType	AskVolume2;

//        TThostFtdcPriceType	BidPrice3;

//        TThostFtdcVolumeType	BidVolume3;

//        TThostFtdcPriceType	AskPrice3;

//        TThostFtdcVolumeType	AskVolume3;

//        TThostFtdcPriceType	BidPrice4;

//        TThostFtdcVolumeType	BidVolume4;

//        TThostFtdcPriceType	AskPrice4;

//        TThostFtdcVolumeType	AskVolume4;

//        TThostFtdcPriceType	BidPrice5;

//        TThostFtdcVolumeType	BidVolume5;

//        TThostFtdcPriceType	AskPrice5;

//        TThostFtdcVolumeType	AskVolume5;

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

CtpMarketDataProvider::CtpMarketDataProvider(const std::string& connection, FreeQuant::MarketDataProvider::Callback *callback) :
    _impl(new CtpMarketDataProvider::Impl(connection, callback)) {
}

CtpMarketDataProvider::~CtpMarketDataProvider() {}

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

