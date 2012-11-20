#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <string>
#include <QDebug>
#include <QMainWindow>
#include <QMessageBox>
#include <QString>

#include <freequant/marketdata/MarketDataProvider.h>
#include <freequant/trade/CtpTradeProvider.h>
#include <freequant/marketdata/CtpMarketDataProvider.h>
#include "commondialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onConnect();
    void onDisconnect();
    void onClear();
    void onReqMktData();
    void onCancelMktData();
//    void onExtord();
//    void onReqCurrentTime();
    void onPlaceOrder();
    void onCancelOrder();
    void onReplaceOrder();
    void onOpenOrders();
    void onFetchOrders();
    void onFetchTrades();
    void onFetchPositions();
    void onQueryExchanges();
    void onQueryInstruments();
    void onQueryInvestor();
//    void onReqOpenOrders();
//    void onReqAllOpenOrders();
//    void onReqAutoOpenOrders();
//    void onReqAccountUpdate();
//    void onReqContractDetails();
//    void onReqIds();
//    void onFinancialAdvisor();
//    void onReqAccts();
private:
    std::unique_ptr<Ui::MainWindow> ui;

    std::unique_ptr<FreeQuant::MarketDataProvider> _md_provider;
    std::shared_ptr<FreeQuant::TradeProvider> trade_provider;
    std::shared_ptr<FreeQuant::CtpTradeProvider> _ctpTradeProvider;
    std::shared_ptr<FreeQuant::CtpMarketDataProvider> _ctpMarketDataProvider;
//    bool faError;

//    bool m_financialAdvisor;
//    std::string m_managedAccounts;

//    std::string faGroupsXML;
//    std::string faProfilesXML;
//    std::string faAliasesXML;
};

#endif // MAINWINDOW_H
