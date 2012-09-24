#include <QUiLoader>
#include <QFile>
#include <QVBoxLayout>
#include <QDebug>

#include "commondialog.h"
#include "ui_commondialog.h"

CommonDialog::CommonDialog(QWidget *parent) : QDialog(parent), ui(new Ui::CommonDialog) {
    ui->setupUi(this);
    QUiLoader loader;
    QFile file(":/forms/orderdialog.ui");
    file.open(QFile::ReadOnly);
    QWidget *widget = loader.load(&file, NULL);
    file.close();
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(widget);
    ui->frame->setLayout(layout);
    setWindowTitle(tr("Text Finder"));
}
