#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <fq/marketdata/ctp/ctpmarketdataprovider.h>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    md_provider = new FreeQuant::MarketData::CtpMarketDataProvider();
}

MainWindow::~MainWindow() {
    delete md_provider;
    delete ui;
}

//void MainWindow::onReqCurrentTime() {
//    m_client->reqCurrentTime();
//}

//void MainWindow::onPlaceOrder() {
//    CommonDialog dialog(this, CommonDialog::OrderDialog);
//    if (dialog.exec() == QDialog::Accepted) {
//        QMap<QString, QVariant>& params = dialog.params();
//        OrderId id =  params.value("id").toInt();
//        Order order = params.value("order").value<Order>();
//        Contract contract = params.value("contract").value<Contract>();
//        m_client->placeOrder(id, contract, order);
//    }
//}

//void MainWindow::onReqOpenOrders() {
//    m_client->reqOpenOrders();
//}

//void MainWindow::onReqAllOpenOrders() {
//    m_client->reqAllOpenOrders();
//}

//void MainWindow::onReqAutoOpenOrders() {
//     m_client->reqAutoOpenOrders(true);
//}

//void MainWindow::onReqAccountUpdate() {

//}

//void MainWindow::onClear() {
//    ui->responseTextEdit->clear();
//    ui->dataTextEdit->clear();
//    ui->errorsTextEdit->clear();
//}

void MainWindow::onConnect() {
    md_provider->connect();
//    CommonDialog dialog(this, CommonDialog::ConnectionDialog);
//    if (dialog.exec() == QDialog::Accepted) {
//        QMap<QString, QVariant> params = dialog.params();

//        QString ip = params.value("ip").toString();
//        unsigned int port = params.value("port").toUInt();
//        int clientId = params.value("clientId").toInt();
//        QString message = QString("Connecting to Tws using clientId %1 ...").arg(clientId);
//        ui->responseTextEdit->append(message);

//        bool success = m_client->eConnect(ip.toAscii(), port, clientId);
//        if (success) {
//            QString message = QString("Connected to Tws server version %1 at %2.").arg(m_client->serverVersion()).arg(m_client->TwsConnectionTime().c_str());
//            ui->responseTextEdit->append(message);
//        }
//    }
}

void MainWindow::onDisconnect() {
    md_provider->disconnect();
}

//void MainWindow::onReqMktData() {
//    CommonDialog dialog(this, CommonDialog::OrderDialog);
//    if (dialog.exec() == QDialog::Accepted) {
//        QMap<QString, QVariant>& params = dialog.params();
//        TickerId id = params.value("id").toInt();;
//        Contract contract = params.value("contract").value<Contract>();
//        std::string genericTicks = params.value("genericTicks").toString().toStdString();
//        bool snapshot = params.value("snapshot").toBool();
//        m_client->reqMktData(id, contract, genericTicks, snapshot);
//    }
// }

//void MainWindow::onExtord() {
//    CommonDialog dialog(this, CommonDialog::OrderAttributesDialog);
//    dialog.exec();
//}

//void MainWindow::onReqIds() {
//    m_client->reqIds(20);
//}

//void MainWindow::onReqContractDetails() {

//}

//void MainWindow::onFinancialAdvisor() {
//    faGroupsXML = faProfilesXML = faAliasesXML = "";
//    faError = false;
//    m_client->requestFA(GROUPS);
//    m_client->requestFA(PROFILES);
//    m_client->requestFA(ALIASES);
//}

//void MainWindow::onReqAccts() {
//    m_client->reqManagedAccts();
//}
