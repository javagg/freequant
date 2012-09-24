/********************************************************************************
** Form generated from reading UI file 'sdialog.ui'
**
** Created: Mon Sep 24 17:12:18 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SDIALOG_H
#define UI_SDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SDialog)
    {
        if (SDialog->objectName().isEmpty())
            SDialog->setObjectName(QString::fromUtf8("SDialog"));
        SDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(SDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(SDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame);

        buttonBox = new QDialogButtonBox(SDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SDialog);
    } // setupUi

    void retranslateUi(QDialog *SDialog)
    {
        SDialog->setWindowTitle(QApplication::translate("SDialog", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SDialog: public Ui_SDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SDIALOG_H
