#-------------------------------------------------
#
# Project created by QtCreator 2012-09-20T20:40:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fqclient
TEMPLATE = app

DEFINES += _AFXDLL IB_USE_STD_STRING
DEFINES -= UNICODE

SOURCES += main.cpp\
    TWS/EPosixClientSocket.cpp \
    TWS/EClientSocketBase.cpp

HEADERS  += mainwindow.h \
    TWS/TwsSocketClientErrors.h \
    TWS/StdAfx.h \
    TWS/shared_ptr.h \
    TWS/ScannerSubscription.h \
    TWS/OrderState.h \
    TWS/Order.h \
    TWS/IBString.h \
    TWS/Execution.h \
    TWS/EWrapper.h \
    TWS/EPosixClientSocketPlatform.h \
    TWS/EPosixClientSocket.h \
    TWS/EClientSocketBaseImpl.h \
    TWS/EClientSocketBase.h \
    TWS/EClient.h \
    TWS/Contract.h \
    TWS/CommonDefs.h

FORMS    += mainwindow.ui \
    orderdialog.ui
