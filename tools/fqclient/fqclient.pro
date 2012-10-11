#-------------------------------------------------
#
# Project created by QtCreator 2012-09-20T20:40:03
#
#-------------------------------------------------

QT += core gui
TARGET = fqclient
TEMPLATE = app
CONFIG += uitools

DEFINES += _AFXDLL IB_USE_STD_STRING
DEFINES -= UNICODE

QMAKE_CFLAGS_DEBUG += -MTd
QMAKE_CFLAGS_RELEASE += -MT

SOURCES += main.cpp\
    commondialog.cpp \
    mainwindow.cpp \

win32 {
    SOURCES += \
        TWS/EClientSocket.cpp \
        TWS/EClientSocketBase_win.cpp
}

unix {
    SOURCES += \
        TWS/EPosixClientSocket_posix.cpp \
}

HEADERS += mainwindow.h \
    commondialog.h \
    TWS/TwsSocketClientErrors.h \
    TWS/StdAfx.h \
    TWS/shared_ptr.h \
    TWS/ScannerSubscription.h \
    TWS/OrderState.h \
    TWS/Order.h \
    TWS/IBString.h \
    TWS/HScrollListBox.h \
    TWS/Execution.h \
    TWS/EWrapper.h \
    TWS/EClientSocketBaseImpl.h \
    TWS/EClientSocketBase.h \
    TWS/EClient.h \
    TWS/Contract.h \
    TWS/CommonDefs.h

win32 {
    HEADERS += \
        TWS/EClientSocket.h
} unix {
    HEADERS += \
        TWS/EPosixClientSocketPlatform.h \
        TWS/EPosixClientSocket.h
}

FORMS += \
    mainwindow.ui \
    commondialog.ui \
    orderattributes.ui \
    order.ui \
    newsbulletins.ui \
    marketscanner.ui \
    logconfiguration.ui \
    executionreportfilter.ui \
    accoutupdate.ui \
    connection.ui

RESOURCES += \
    forms.qrc
