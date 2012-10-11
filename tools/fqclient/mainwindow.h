#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <QDebug>
#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QSharedPointer>

#include "TWS/EClient.h"
#include "TWS/EWrapper.h"
#include "ui_mainwindow.h"
#include "commondialog.h"

#ifndef USE_POSIX
  #include "TWS/EClientSocket.h"
#else
  #include "TWS/EPosixClientSocket.h"
#endif

#include "TWS/Contract.h"

Q_DECLARE_METATYPE(Contract)

class MainWindow : public QMainWindow, public EWrapper
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0): QMainWindow(parent), ui(new Ui::MainWindow) {
        ui->setupUi(this);
#ifndef USE_POSIX
        m_client = QSharedPointer<EClient>(new EClientSocket(this));
#else
        m_client = QSharedPointer<EClient>(new EPosixClientSocket(this));
#endif
    }

    ~MainWindow() {
        delete ui;
    }

    virtual void tickPrice(TickerId tickerId, TickType tickType, double price, int canAutoExecute);
    virtual void tickSize(TickerId tickerId, TickType tickType, int size){
        QString str = QString("id=%1 %2=%3").arg(tickerId).arg(tickTypeToTickField(tickType)).arg(size);
        ui->dataTextEdit->append(str);
    }

    virtual void tickOptionComputation( TickerId tickerId, TickType tickType, double impliedVol, double delta,
        double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice){

    }

    virtual void tickGeneric(TickerId tickerId, TickType tickType, double value){
        QString str = QString("id=%1 %2=%3").arg(tickerId).arg(tickTypeToTickField(tickType)).arg(value);
        ui->dataTextEdit->append(str);
   }

    virtual void tickString(TickerId tickerId, TickType tickType, const IBString& value){
        QString str = QString("id=%1 %2=%3").arg(tickerId).arg(tickTypeToTickField(tickType)).arg(value.c_str());
        ui->dataTextEdit->append(str);
    }

    virtual void tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const IBString& formattedBasisPoints,
        double totalDividends, int holdDays, const IBString& futureExpiry, double dividendImpact, double dividendsToExpiry) {
        QString str = QString("id=%1  %2: basisPoints=%3 / %4 impliedFuture=%5 holdDays=%6 futureExpiry=%7 dividendImpact=%8 dividendsToExpiry=%9").
                arg(tickerId).arg(tickTypeToTickField(tickType)).arg(basisPoints).arg(formattedBasisPoints.c_str()).arg(totalDividends).arg(holdDays).arg(futureExpiry.c_str()).arg(dividendImpact).arg(dividendsToExpiry);
        ui->dataTextEdit->append(str);
    }

    virtual void orderStatus( OrderId orderId, const IBString &status, int filled,
        int remaining, double avgFillPrice, int permId, int parentId,
        double lastFillPrice, int clientId, const IBString& whyHeld) {
        QString str = QString("orderId=%1 clientId=%2 permId=%3 status=%4  filled=%5  remaining=%6  avgFillPrice=%7 lastFillPrice=%8 parentId=%9 whyHeld=%10")
                .arg(orderId).arg(clientId).arg(permId).arg(status.c_str()).arg(filled).arg(remaining).arg(avgFillPrice).arg(lastFillPrice).arg(parentId).arg(whyHeld.c_str());
        ui->dataTextEdit->append(str);
    }

    virtual void openOrder( OrderId orderId, const Contract&, const Order&, const OrderState&){

    }

    virtual void openOrderEnd() {
        ui->errorsTextEdit->append(" =============== end ===============");
    }

    virtual void winError(const IBString& str, int lastError) {
        QString errorStr = QString("[winError]Error Code: %1 | Error Msg: %2 ").arg(lastError).arg(str.c_str());
        ui->errorsTextEdit->append(errorStr);
    }

    virtual void connectionClosed() {
        qDebug() << "connectionClosed";
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
        ui->errorsTextEdit->append(QString("id =%1 =============== end ===============").arg(reqId));
    }

    virtual void execDetails( int reqId, const Contract& contract, const Execution& execution) {
//        ui->errorsTextEdit->append("---- Execution Details begin ----");
//        ui->errorsTextEdit->append(QString("execDetails: reqId=%1").arg(reqId));

    }

    virtual void execDetailsEnd( int reqId) {

    }

    virtual void error(const int id, const int errorCode, const IBString errorString);
    virtual void updateMktDepth(TickerId id, int position, int operation, int side,
       double price, int size) {

    }

    virtual void updateMktDepthL2(TickerId id, int position, IBString marketMaker, int operation,
       int side, double price, int size) {

    }

    virtual void updateNewsBulletin(int msgId, int msgType, const IBString& newsMessage, const IBString& originExch) {
        QMessageBox::information(this, "", QString("MsgId=%1 :: MsgType = %2 :: Origin= %3 :: Message= %4").arg(msgId).arg(msgType).arg(originExch.c_str()).arg(newsMessage.c_str()));
    }

    virtual void managedAccounts(const IBString& accountsList);
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
        ui->responseTextEdit->append(QString("id=%i =============== end ===============").arg(reqId));
    }

    virtual void marketDataType( TickerId reqId, int marketDataType) {
        QString dataType = QString();
        switch (marketDataType){
            case REALTIME:
                dataType = "Real-Time";
                break;
            case FROZEN:
                dataType = "Frozen";
                break;
            default:
                dataType = "Unknown";
        }
        ui->responseTextEdit->append(QString("id=%1 marketDataType=%2").arg(reqId).arg(dataType));
    }

public slots:
    void onConnect();
    void onDisconnect();
    void onClear();
    void onReqMktData();
    void onExtord();
    void onReqCurrentTime();
    void onPlaceOrder();
    void onReqOpenOrders();
    void onReqAllOpenOrders();
    void onReqAutoOpenOrders();
    void onReqAccountUpdate();
    void onReqContractDetails();
    void onReqIds();
    void onFinancialAdvisor();
    void onReqAccts();
private:
    Ui::MainWindow *ui;

    QSharedPointer<EClient> m_client;
    bool faError;

    bool m_financialAdvisor;
    IBString m_managedAccounts;

    std::string faGroupsXML;
    std::string faProfilesXML;
    std::string faAliasesXML;
    QString tickTypeToTickField(TickType field);
};

#endif // MAINWINDOW_H
