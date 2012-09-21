#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "TWS/EPosixClientSocket.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    client = new EPosixClientSocket(this);
    //connect(this, SIGNAL(), this, SLOT())
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::onConnect() {

}*/
