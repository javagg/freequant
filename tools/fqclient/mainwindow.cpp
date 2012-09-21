#include <iostream>
#include <string>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "TWS/EPosixClientSocket.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_client = new EPosixClientSocket(this);
    //connect(this, SIGNAL(), this, SLOT())
}

MainWindow::~MainWindow()
{
    delete m_client;
    delete ui;

}

void MainWindow::onConnect() {
        QMessageBox::about(NULL, "About", "About this application");

//        QString displayString;


        // You get "~/Tom-Jane.txt"

////            CString displayString;
//            displayString.Format( "Connecting to Tws using clientId %d ...", dlg.m_clientId);
//            int i = m_orderStatus.AddString( displayString);
//            m_orderStatus.SetTopIndex( i);
////        }
        string ip = "localhost";
        unsigned int port = 4267;
        int clientId = 0;

        QString("Connecting to Tws using clientId %d ...").arg(clientId);

        m_client->eConnect(ip.c_str(), port, clientId);

        if( m_client->serverVersion() > 0)	{
//            string displayString;
//        //    displayString.Format( "Connected to Tws server version %d at %s.",
//                m_client->serverVersion(), m_client->TwsConnectionTime());
//            int i = m_orderStatus.AddString( displayString);
//            m_orderStatus.SetTopIndex( i);
        }

}
