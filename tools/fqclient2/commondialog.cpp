#include <string>

#include <QtUiTools/QUiLoader>
#include <QFile>
#include <QVBoxLayout>
#include <QDebug>
#include <QCheckBox>

#include "commondialog.h"
#include "ui_commondialog.h"

//CommonDialog::CommonDialog(QWidget *parent, Type type) : QDialog(parent), ui(new Ui::CommonDialog), type(type) {
//    ui->setupUi(this);
//    QUiLoader loader;
//    QString uifile;
//    switch (type) {
//    case ConnectionDialog:
//        uifile = "connection.ui";
//        break;
//    case OrderDialog:
//        uifile = "order.ui";
//        break;
//    case OrderAttributesDialog:
//        uifile = "orderattributes.ui";
//        break;
//    case EmptyDialog:
//    default:
//        uifile = "";
//    }

//    QFile file(QString(":/forms/") + uifile);
//    file.open(QFile::ReadOnly);
//    QWidget *widget = loader.load(&file);
//    file.close();
//    QVBoxLayout *layout = new QVBoxLayout;
//    layout->addWidget(widget);
//    ui->frame->setLayout(layout);
//}

//void CommonDialog::acceptForConnection() {
//    QString ip = ui->frame->findChild<QLineEdit*>("ipLineEdit")->text();
//    m_params.insert("ip", QVariant(ip));
//    unsigned int port = ui->frame->findChild<QLineEdit*>("portLineEdit")->text().toUInt();
//    m_params.insert("port", QVariant(port));
//    int clientId = ui->frame->findChild<QLineEdit*>("clientIdLineEdit")->text().toInt();
//    m_params.insert("clientId", QVariant(clientId));
//}

//void CommonDialog::acceptForOrder() {
//    QLineEdit *idLineEdit = ui->frame->findChild<QLineEdit*>("idLineEdit");
//    int clientId = 0;
//    if (idLineEdit) {
//        clientId = idLineEdit->text().toInt();
//         m_params.insert("id", QVariant(clientId));
//    }

//    Contract contract;
//    contract.conId = ui->frame->findChild<QLineEdit*>("contractIdLineEdit")->text().toLong();
//    contract.symbol = ui->frame->findChild<QLineEdit*>("symbolLineEdit")->text().toStdString();
//    contract.secType = ui->frame->findChild<QLineEdit*>("typeLineEdit")->text().toStdString();
//    contract.expiry = ui->frame->findChild<QLineEdit*>("expiryLineEdit")->text().toStdString();
//    contract.strike = ui->frame->findChild<QLineEdit*>("strikeLineEdit")->text().toDouble();
//    contract.exchange = ui->frame->findChild<QLineEdit*>("exchangeLineEdit")->text().toStdString();
//    contract.right = ui->frame->findChild<QLineEdit*>("rightLineEdit")->text().toStdString();
//    contract.multiplier = ui->frame->findChild<QLineEdit*>("multiplierLineEdit")->text().toStdString();
//    contract.primaryExchange = ui->frame->findChild<QLineEdit*>("primaryExchangeLineEdit")->text().toStdString();
//    contract.currency = ui->frame->findChild<QLineEdit*>("currencyLineEdit")->text().toStdString();
//    contract.localSymbol = ui->frame->findChild<QLineEdit*>("localSymbolLineEdit")->text().toStdString();
//    contract.includeExpired = ui->frame->findChild<QLineEdit*>("includeExpiredLineEdit")->text().toInt();
//    contract.secIdType = ui->frame->findChild<QLineEdit*>("secIdTypeLineEdit")->text().toStdString();

//    QVariant c; c.setValue(contract);
//    m_params.insert("contract", c);

//    QString genericTicks = ui->frame->findChild<QLineEdit*>("genericTicksLineEdit")->text();
//    bool snapshot = ui->frame->findChild<QCheckBox*>("snapshotCheckBox")->checkState() == Qt::Checked;
//    m_params.insert("genericTicks", QVariant(genericTicks));
//    m_params.insert("snapshot", QVariant(snapshot));

////    Order order;
////    order.orderId = ui->frame->findChild<QLineEdit*>("orderIdLineEdit")->text().toLong();
////    order.action = ui->frame->findChild<QLineEdit*>("actionLineEdit")->text().toStdString();
////    order.totalQuantity = ui->frame->findChild<QLineEdit*>("totalQuantityLineEdit")->text().toLong();
////    order.orderType = ui->frame->findChild<QLineEdit*>("orderTypeLineEdit")->text().toStdString();
////    order.lmtPrice = ui->frame->findChild<QLineEdit*>("lmtPriceLineEdit")->text().toDouble();
////    order.auxPrice = ui->frame->findChild<QLineEdit*>("auxPriceLineEdit")->text().toDouble();
////    QVariant o; o.setValue(order);
////    m_params.insert("order", o);
//}

void CommonDialog::accept() {
//    switch (type) {
//    case ConnectionDialog:
//        acceptForConnection();
//        break;
//    case OrderDialog:
//        acceptForOrder();
//        break;
//    case EmptyDialog:
//    default:
//        break;
//    }
    QDialog::accept();
}
