#include "CtpSseTradeProvider.h"
#include "ThostFtdcTraderApiSSE.h"

namespace FreeQuant {

class CtpSseTradeProvider::Impl : public CZQThostFtdcTraderSpi {
public:
    static int requestId;
    Impl(const std::string& connection, FreeQuant::TradeProvider::Callback *callback = 0) {

    }

    // Fix 4.4
    void updatePassword(const std::string& oldPassword, const std::string& newPassword) {
        CZQThostFtdcUserPasswordUpdateField field = {};
        oldPassword.copy(field.OldPassword, oldPassword.size());
        newPassword.copy(field.NewPassword, newPassword.size());
        api->ReqUserPasswordUpdate(&field, ++requestId);
    }

    void OnRspUserPasswordUpdate(CZQThostFtdcUserPasswordUpdateField *field, CZQThostFtdcRspInfoField *info, int requestID, bool last) {
//        field->NewPassword;
    }

    // Fix 5.0.sp1
    void queryMaxVol(const std::string& symbol) {
        CZQThostFtdcQueryMaxOrderVolumeField field = {};
        api->ReqQueryMaxOrderVolume(&field, ++requestId);
    }

    // Fix 4.3 TradeCaptureReport
    void queryTrade() {
        CZQThostFtdcQryTradeField field = {};
        api->ReqQryTrade(&field, ++requestId);
    }

    // Fix 4.4 Position Report
    void queryPosition() {
        CZQThostFtdcQryInvestorPositionField field = {};
        api->ReqQryInvestorPosition(&field, ++requestId);
//        api->ReqQryInvestorPositionDetail
    }

    void queryAccount() {
        CZQThostFtdcQryTradingAccountField field = {};
        api->ReqQryTradingAccount(&field, ++requestId);
    }

    void queryInstrument() {

        // Fix
//        api->ReqQryInstrumentCommissionRate();
    }

    void queryExchange() {
        CZQThostFtdcQryExchangeField field = {};
        api->ReqQryExchange(&field, ++requestId);
    }

    // rarely used
    void OnRspQryExchange(CZQThostFtdcExchangeField *field, CZQThostFtdcRspInfoField *info, int requestID, bool last) {
//        field->ExchangeProperty
    }

//    void OnFrontConnected() {};
//    void OnFrontDisconnected(int nReason) {};
//    void OnHeartBeatWarning(int nTimeLapse) {};
//    void OnRspUserLogin(CZQThostFtdcRspUserLoginField *pRspUserLogin, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
//    void OnRspUserLogout(CZQThostFtdcUserLogoutField *pUserLogout, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
//    void OnRspError(CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
//    void OnRspSubMarketData(CZQThostFtdcSpecificInstrumentField *pSpecificInstrument, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
//    void OnRspUnSubMarketData(CZQThostFtdcSpecificInstrumentField *pSpecificInstrument, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
//    void OnRtnDepthMarketData(CZQThostFtdcDepthMarketDataField *pDepthMarketData) {};
private:
    CZQThostFtdcTraderApi *api;
};

int CtpSseTradeProvider::Impl::requestId = 0;

//CtpSseMarketDataProvider::CtpSseMarketDataProvider(const std::string& connection,
//    FreeQuant::MarketDataProvider::Callback *callback) :
//    _impl(new CtpSseMarketDataProvider::Impl(connection, callback)) {

//}

//CtpSseMarketDataProvider::~CtpSseMarketDataProvider() {}

//void CtpSseMarketDataProvider::setCallback(Callback *callback) {

//}

//void CtpSseMarketDataProvider::setCallback(MarketDataProviderCallback *callback) {

//}

//void CtpSseMarketDataProvider::connect(bool block) {

//}

//void CtpSseMarketDataProvider::disconnect(bool block) {

//}

//bool CtpSseMarketDataProvider::isConnected() const {
//    return false;
//}

//std::string CtpSseMarketDataProvider::name() const {
//    return "CTPSSE";
//}

//void CtpSseMarketDataProvider::subscribe(const Symbols& symbols) {

//}

//void CtpSseMarketDataProvider::unsubscribe(const Symbols& symbols) {

//}

//void CtpSseMarketDataProvider::subscribe(const std::string& symbol) {

//}

//void CtpSseMarketDataProvider::unsubscribe(const std::string& symbol) {

//}

}
