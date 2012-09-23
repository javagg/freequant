#include <QUiLoader>
#include <QFile>
#include <QVBoxLayout>
#include <QDebug>

#include "commondialog.h"

CommonDialog::CommonDialog(QWidget *parent) : QDialog(parent) {
    QUiLoader loader;
    QFile file(":/forms/orderdialog.ui");
    file.open(QFile::ReadOnly);
    QWidget *widget = loader.load(&file, this);
    file.close();
//    QVBoxLayout *layout = new QVBoxLayout;
//    layout->addWidget(widget);
//    qDebug() << widget->children();
//    setLayout(layout);
//    setWindowTitle(tr("Text Finder"));
}
