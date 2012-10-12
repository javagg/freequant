TEMPLATE = app
CONFIG += console
CONFIG -= qt

DEFINES += _AFXDLL IB_USE_STD_STRING
DEFINES -= UNICODE

SOURCES += main.cpp \
    tws/EPosixClientSocket.cpp \
    tws/EClientSocketBase.cpp \
    PosixTestClient.cpp

HEADERS += \
    tws/TwsSocketClientErrors.h \
    tws/TagValue.h \
    tws/StdAfx.h \
    tws/shared_ptr.h \
    tws/ScannerSubscription.h \
    tws/OrderState.h \
    tws/Order.h \
    tws/IBString.h \
    tws/HScrollListBox.h \
    tws/Execution.h \
    tws/EWrapper.h \
    tws/EPosixClientSocketPlatform.h \
    tws/EPosixClientSocket.h \
    tws/EClientSocketBaseImpl.h \
    tws/EClientSocketBase.h \
    tws/EClientSocket.h \
    tws/EClient.h \
    tws/Contract.h \
    tws/CommonDefs.h \
    tws/CommissionReport.h

