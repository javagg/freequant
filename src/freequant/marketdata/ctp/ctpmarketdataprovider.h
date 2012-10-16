#ifndef FQ_MARKETDATA_CTP_CTPPROVIDER_H
#define FQ_MARKETDATA_CTP_CTPPROVIDER_H

#include <mutex>
#include <condition_variable>

#include <freequant/marketdata/marketdataprovider.h>
#include "api/trade/win/public/ThostFtdcMdApi.h"

namespace FreeQuant {

class CtpMarketDataProvider : public MarketDataProvider, private CThostFtdcMdSpi {
public:
    explicit CtpMarketDataProvider();
    virtual ~CtpMarketDataProvider();
    virtual void connect(bool block = true);
    virtual void disconnect(bool block = true);
    virtual bool isConnected() const;
    virtual std::string name() const { return "CTP"; }
    virtual void subscribe(std::vector<std::string> symbols);
    virtual void unsubscribe(std::vector<std::string> symbols);

    void onConnected();
    void onDisconnected();

private:
    std::mutex mutex;
    std::condition_variable condition;

    CThostFtdcMdApi *api;
    bool m_connected;
    void OnFrontConnected();
    void OnFrontDisconnected(int nReason);
    void OnHeartBeatWarning(int nTimeLapse);
    void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);

    bool errorOccurred(CThostFtdcRspInfoField *rspInfo);
};

} // namespace FreeQuant

#endif // FQ_MARKETDATA_CTP_CTPPROVIDER_H
