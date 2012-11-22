#include "CtpSseMarketDataProvider.h"
#include "ThostFtdcMdApiSSE.h"
#include "ThostFtdcTraderApiSSE.h"

namespace FreeQuant { namespace Ext {

class CtpSseMarketDataProvider::Impl : public CZQThostFtdcMdSpi {
public:
    Impl(const std::string& connection, FreeQuant::MarketDataProvider::Callback *callback = 0) {

    }
    void OnFrontConnected() {};
    void OnFrontDisconnected(int nReason) {};
    void OnHeartBeatWarning(int nTimeLapse) {};
    void OnRspUserLogin(CZQThostFtdcRspUserLoginField *pRspUserLogin, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspUserLogout(CZQThostFtdcUserLogoutField *pUserLogout, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspError(CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspSubMarketData(CZQThostFtdcSpecificInstrumentField *pSpecificInstrument, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRspUnSubMarketData(CZQThostFtdcSpecificInstrumentField *pSpecificInstrument, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    void OnRtnDepthMarketData(CZQThostFtdcDepthMarketDataField *pDepthMarketData) {};
private:
    CZQThostFtdcMdApi *_api;
};

CtpSseMarketDataProvider::CtpSseMarketDataProvider(const std::string& connection,
    FreeQuant::MarketDataProvider::Callback *callback) :
    _impl(new CtpSseMarketDataProvider::Impl(connection, callback)) {

}

CtpSseMarketDataProvider::~CtpSseMarketDataProvider() {}

void CtpSseMarketDataProvider::setCallback(Callback *callback) {

}

void CtpSseMarketDataProvider::connect(bool block) {

}

void CtpSseMarketDataProvider::disconnect(bool block) {

}

bool CtpSseMarketDataProvider::isConnected() const {
    return false;
}

const std::string& CtpSseMarketDataProvider::name() const {
    return "CTPSSE";
}

void CtpSseMarketDataProvider::subscribe(const Symbols& symbols) {

}

void CtpSseMarketDataProvider::unsubscribe(const Symbols& symbols) {

}

}}
