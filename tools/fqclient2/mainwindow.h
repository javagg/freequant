#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <QDebug>
#include <QMainWindow>
#include <QMessageBox>
#include <QString>

#include <freequant/marketdata/MarketDataProvider.h>
#include <freequant/trade/FixTradeProvider.h>

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
//    void onReqOpenOrders();
//    void onReqAllOpenOrders();
//    void onReqAutoOpenOrders();
//    void onReqAccountUpdate();
//    void onReqContractDetails();
//    void onReqIds();
//    void onFinancialAdvisor();
//    void onReqAccts();
private:
    Ui::MainWindow *ui;

    FreeQuant::MarketDataProvider *md_provider;
    FreeQuant::TradeProvider *trade_provider;
    bool faError;

    bool m_financialAdvisor;
    std::string m_managedAccounts;

    std::string faGroupsXML;
    std::string faProfilesXML;
    std::string faAliasesXML;
};

#endif // MAINWINDOW_H
