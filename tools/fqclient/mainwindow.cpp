#include "mainwindow.h"
#include "TWS/Order.h"
Q_DECLARE_METATYPE(Order)

QString MainWindow::tickTypeToTickField(TickType tickType) {
    switch( tickType)
    {
        case BID_SIZE:	                    return "bidSize";
        case BID:		                    return "bidPrice";
        case ASK:		                    return "askPrice";
        case ASK_SIZE:	                    return "askSize";
        case LAST:		                    return "lastPrice";
        case LAST_SIZE:	                    return "lastSize";
        case HIGH:		                    return "high";
        case LOW:		                    return "low";
        case VOLUME:	                    return "volume";
        case CLOSE:		                    return "close";
        case BID_OPTION_COMPUTATION:		return "bidOptComp";
        case ASK_OPTION_COMPUTATION:		return "askOptComp";
        case LAST_OPTION_COMPUTATION:		return "lastOptComp";
        case MODEL_OPTION:					return "optionModel";
        case OPEN:                          return "open";
        case LOW_13_WEEK:                   return "13WeekLow";
        case HIGH_13_WEEK:                  return "13WeekHigh";
        case LOW_26_WEEK:                   return "26WeekLow";
        case HIGH_26_WEEK:                  return "26WeekHigh";
        case LOW_52_WEEK:                   return "52WeekLow";
        case HIGH_52_WEEK:                  return "52WeekHigh";
        case AVG_VOLUME:                    return "AvgVolume";
        case OPEN_INTEREST:                 return "OpenInterest";
        case OPTION_HISTORICAL_VOL:         return "OptionHistoricalVolatility";
        case OPTION_IMPLIED_VOL:            return "OptionImpliedVolatility";
        case OPTION_BID_EXCH:               return "OptionBidExchStr";
        case OPTION_ASK_EXCH:               return "OptionAskExchStr";
        case OPTION_CALL_OPEN_INTEREST:     return "OptionCallOpenInterest";
        case OPTION_PUT_OPEN_INTEREST:      return "OptionPutOpenInterest";
        case OPTION_CALL_VOLUME:            return "OptionCallVolume";
        case OPTION_PUT_VOLUME:             return "OptionPutVolume";
        case INDEX_FUTURE_PREMIUM:          return "IndexFuturePremium";
        case BID_EXCH:                      return "bidExch";
        case ASK_EXCH:                      return "askExch";
        case AUCTION_VOLUME:                return "auctionVolume";
        case AUCTION_PRICE:                 return "auctionPrice";
        case AUCTION_IMBALANCE:             return "auctionImbalance";
        case MARK_PRICE:                    return "markPrice";
        case BID_EFP_COMPUTATION:           return "bidEFP";
        case ASK_EFP_COMPUTATION:           return "askEFP";
        case LAST_EFP_COMPUTATION:          return "lastEFP";
        case OPEN_EFP_COMPUTATION:          return "openEFP";
        case HIGH_EFP_COMPUTATION:          return "highEFP";
        case LOW_EFP_COMPUTATION:           return "lowEFP";
        case CLOSE_EFP_COMPUTATION:         return "closeEFP";
        case LAST_TIMESTAMP:                return "lastTimestamp";
        case SHORTABLE:                     return "shortable";
        case FUNDAMENTAL_RATIOS:            return "fundamentals";
        case RT_VOLUME:                     return "RTVolume";
        case HALTED:                        return "halted";
        case BID_YIELD:                     return "bidYield";
        case ASK_YIELD:                     return "askYield";
        case LAST_YIELD:                    return "lastYield";
        case CUST_OPTION_COMPUTATION:       return "custOptComp";
        case TRADE_COUNT:                   return "trades";
        case TRADE_RATE:                    return "trades/min";
        case VOLUME_RATE:                   return "volume/min";
        case LAST_RTH_TRADE:                return "lastRTHTrade";
        default:                            return "unknown";
    }
}

void MainWindow::onReqCurrentTime() {
    m_client->reqCurrentTime();
}

void MainWindow::onPlaceOrder() {
    CommonDialog dialog(this, CommonDialog::OrderDialog);
    if (dialog.exec() == QDialog::Accepted) {
        QMap<QString, QVariant>& params = dialog.params();
        OrderId id =  params.value("id").toInt();
        Order order = params.value("order").value<Order>();
        Contract contract = params.value("contract").value<Contract>();
        m_client->placeOrder(id, contract, order);
    }
}

void MainWindow::onReqOpenOrders() {
    m_client->reqOpenOrders();
}

void MainWindow::onReqAllOpenOrders() {
    m_client->reqAllOpenOrders();
}

void MainWindow::onReqAutoOpenOrders() {
     m_client->reqAutoOpenOrders(true);
}

void MainWindow::onReqAccountUpdate() {

}

void MainWindow::onClear() {
    ui->responseTextEdit->clear();
    ui->dataTextEdit->clear();
    ui->errorsTextEdit->clear();
}

void MainWindow::onConnect() {
    CommonDialog dialog(this, CommonDialog::ConnectionDialog);
    if (dialog.exec() == QDialog::Accepted) {
        QMap<QString, QVariant> params = dialog.params();

        QString ip = params.value("ip").toString();
        unsigned int port = params.value("port").toUInt();
        int clientId = params.value("clientId").toInt();
        QString message = QString("Connecting to Tws using clientId %1 ...").arg(clientId);
        ui->responseTextEdit->append(message);

        bool success = m_client->eConnect(ip.toAscii(), port, clientId);
        if (success) {
            QString message = QString("Connected to Tws server version %1 at %2.").arg(m_client->serverVersion()).arg(m_client->TwsConnectionTime().c_str());
            ui->responseTextEdit->append(message);
        }
    }
}

void MainWindow::onDisconnect() {
    m_client->eDisconnect();
}

void MainWindow::onReqMktData() {
    CommonDialog dialog(this, CommonDialog::OrderDialog);
    if (dialog.exec() == QDialog::Accepted) {
        QMap<QString, QVariant>& params = dialog.params();
        TickerId id = params.value("id").toInt();;
        Contract contract = params.value("contract").value<Contract>();
        std::string genericTicks = params.value("genericTicks").toString().toStdString();
        bool snapshot = params.value("snapshot").toBool();
        m_client->reqMktData(id, contract, genericTicks, snapshot);
    }
 }

void MainWindow::onExtord() {
    CommonDialog dialog(this, CommonDialog::OrderAttributesDialog);
    dialog.exec();
}

void MainWindow::onReqIds() {
    m_client->reqIds(20);
}

void MainWindow::onReqContractDetails() {

}

void MainWindow::onFinancialAdvisor() {
    faGroupsXML = faProfilesXML = faAliasesXML = "";
    faError = false;
    m_client->requestFA(GROUPS);
    m_client->requestFA(PROFILES);
    m_client->requestFA(ALIASES);
}

void MainWindow::onReqAccts() {
    m_client->reqManagedAccts();
}
