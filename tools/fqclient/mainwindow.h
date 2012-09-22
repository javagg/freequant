#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <QDebug>
#include <QMainWindow>
#include <QMessageBox>

#include "TWS/EClient.h"
#include "TWS/EWrapper.h"
#include "ui_mainwindow.h"
#include "commondialog.h"

#include "TWS/EPosixClientSocket.h"

#include "TWS/Contract.h"
Q_DECLARE_METATYPE(Contract)

class MainWindow : public QMainWindow, public EWrapper
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0): QMainWindow(parent), ui(new Ui::MainWindow) {
        ui->setupUi(this);
        m_client = new EPosixClientSocket(this);
    }

    ~MainWindow() {
        delete m_client;
        delete ui;
    }

    virtual void tickPrice( TickerId tickerId, TickType field, double price, int canAutoExecute) {

    }

    virtual void tickSize( TickerId tickerId, TickType field, int size){

    }

    virtual void tickOptionComputation( TickerId tickerId, TickType tickType, double impliedVol, double delta,
        double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice){

    }

    virtual void tickGeneric(TickerId tickerId, TickType tickType, double value){

    }

    virtual void tickString(TickerId tickerId, TickType tickType, const IBString& value){

    }

    virtual void tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const IBString& formattedBasisPoints,
        double totalDividends, int holdDays, const IBString& futureExpiry, double dividendImpact, double dividendsToExpiry) {

    }

    virtual void orderStatus( OrderId orderId, const IBString &status, int filled,
        int remaining, double avgFillPrice, int permId, int parentId,
        double lastFillPrice, int clientId, const IBString& whyHeld) {

    }

    virtual void openOrder( OrderId orderId, const Contract&, const Order&, const OrderState&){

    }

    virtual void openOrderEnd() {

    }

    virtual void winError( const IBString &str, int lastError) {

    }

    virtual void connectionClosed() {
        qDebug("connectionClosed");
    }

    virtual void updateAccountValue(const IBString& key, const IBString& val,
    const IBString& currency, const IBString& accountName) {

    }

    virtual void updatePortfolio( const Contract& contract, int position,
       double marketPrice, double marketValue, double averageCost,
       double unrealizedPNL, double realizedPNL, const IBString& accountName) {

    }

    virtual void updateAccountTime(const IBString& timeStamp) {

    }

    virtual void accountDownloadEnd(const IBString& accountName) {

    }

    virtual void nextValidId( OrderId orderId) {

    }

    virtual void contractDetails( int reqId, const ContractDetails& contractDetails) {

    }

    virtual void bondContractDetails( int reqId, const ContractDetails& contractDetails) {

    }

    virtual void contractDetailsEnd( int reqId) {

    }

    virtual void execDetails( int reqId, const Contract& contract, const Execution& execution) {

    }

    virtual void execDetailsEnd( int reqId) {

    }

    virtual void error(const int id, const int errorCode, const IBString errorString) {

    }

    virtual void updateMktDepth(TickerId id, int position, int operation, int side,
       double price, int size) {

    }

    virtual void updateMktDepthL2(TickerId id, int position, IBString marketMaker, int operation,
       int side, double price, int size) {

    }

    virtual void updateNewsBulletin(int msgId, int msgType, const IBString& newsMessage, const IBString& originExch) {

    }

    virtual void managedAccounts( const IBString& accountsList){

    }

    virtual void receiveFA(faDataType pFaDataType, const IBString& cxml){

    }

    virtual void historicalData(TickerId reqId, const IBString& date, double open, double high,
        double low, double close, int volume, int barCount, double WAP, int hasGaps) {

    }

    virtual void scannerParameters(const IBString &xml) {

    }

    virtual void scannerData(int reqId, int rank, const ContractDetails &contractDetails,
        const IBString &distance, const IBString &benchmark, const IBString &projection,
        const IBString &legsStr) {

    }

    virtual void scannerDataEnd(int reqId) {

    }

    virtual void realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
        long volume, double wap, int count) {

    }

    virtual void currentTime(long time) {
        qDebug("currentTime:",time);
    }

    virtual void fundamentalData(TickerId reqId, const IBString& data) {

    }

    virtual void deltaNeutralValidation(int reqId, const UnderComp& underComp) {

    }

    virtual void tickSnapshotEnd( int reqId) {

    }

    virtual void marketDataType( TickerId reqId, int marketDataType) {

    }

public slots:
    void onConnect() {
        QString ip = "127.0.0.1";
        unsigned int port = 7496;
        int clientId = 0;
        QString message = QString("Connecting to Tws using clientId %1 ...").arg(clientId);
        bool success = m_client->eConnect(ip.toAscii(), port, clientId);
        if (success) {
            QString message = QString("Connected to Tws server version %1 at %2.").arg(m_client->serverVersion()).arg(m_client->TwsConnectionTime().c_str());
            qDebug() << message;
        }
    }

    void onDisconnect() {
        m_client->eDisconnect();
    }

    void onReqMktData() {
        CommonDialog dialog(this);
        dialog.exec();

        QMap<QString, QVariant> params;
        params.insert("qty", QVariant(123));

        qDebug() << params;

        qDebug() << params.value("qty").toInt();
//        QMessageBox::about(NULL, "", "");

        // run dlg box
//        m_dlgOrder->init( this, "Request Market Data", CDlgOrder::REQ_MKT_DATA, m_managedAccounts);
//        if( m_dlgOrder->DoModal() != IDOK) return;

        TickerId id = 222;
        Contract contract = params.value("contract").value<Contract>();
        std::string genericTicks = "123";
        bool snapshot = false;
        m_client->reqMktData(id, contract, genericTicks, snapshot);
    }

private:
    Ui::MainWindow *ui;
    EClient *m_client;
};

#endif // MAINWINDOW_H
