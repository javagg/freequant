#include "commondialog.h"
#include "ui_commondialog.h"

CommonDialog::CommonDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CommonDialog)
{
    ui->setupUi(this);
}

CommonDialog::~CommonDialog()
{
    delete ui;
}
