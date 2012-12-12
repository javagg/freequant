#include <cstring>
#include <iostream>
#include <vector>

#include <boost/format.hpp>

#include <freequant/marketdata/Tick.h>
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
        _callback(callback), _api(0), _connected(false)
    {
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
            _notifier.call1(func);
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
        _notifier.call1(func);
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

            _notifier.complete1();
         }
    }

    void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        cerr << "--->>> " << __FUNCTION__ << endl;
    }

    void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        cout << __FUNCTION__ << endl;
        if (bIsLast) {
            _notifier.complete1(nRequestID);
        }
    }

    void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *specificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
            cerr << __FUNCTION__ << endl;
            cerr << "subscribe " <<  specificInstrument->InstrumentID << endl;
            if (!errorOccurred(pRspInfo)) {
                if (bIsLast) {
                    _notifier.complete1();
                }
            }
    }

    void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *specificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        cerr << __FUNCTION__ << endl;
        cerr << "unsubscribe " << specificInstrument->InstrumentID << endl;
    }

    void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *data) {
        string str = boost::str(boost::format("%s %s.%s") % data->TradingDay %
            data->UpdateTime % data->UpdateMillisec);
        Tick tick;
        tick.datetime = DateTime(str, "%Y%m%d %H:%M:%S%F");
        tick.symbol = data->InstrumentID;
        tick.open = data->OpenPrice;
        tick.ask = data->AskPrice1;

        if (_callback) _callback->onTick(tick);
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

void CtpMarketDataProvider::setCallback(MarketDataProviderCallback *callback) {
//    _impl->setCallback(callback);
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

void CtpMarketDataProvider::subscribe(const std::string& symbol) {

}

void CtpMarketDataProvider::unsubscribe(const std::string& symbol) {

}

} // namespace FreeQuant

