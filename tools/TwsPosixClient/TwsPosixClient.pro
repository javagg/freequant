TEMPLATE = app
CONFIG += console
CONFIG -= qt

DEFINES += _AFXDLL IB_USE_STD_STRING
DEFINES -= UNICODE

SOURCES += main.cpp \
    EPosixClientSocket.cpp \
    EClientSocketBase.cpp \
    PosixTestClient.cpp

HEADERS += \
    TwsSocketClientErrors.h \
    TagValue.h \
    StdAfx.h \
    shared_ptr.h \
    ScannerSubscription.h \
    OrderState.h \
    Order.h \
    IBString.h \
    HScrollListBox.h \
    Execution.h \
    EWrapper.h \
    EPosixClientSocketPlatform.h \
    EPosixClientSocket.h \
    EClientSocketBaseImpl.h \
    EClientSocketBase.h \
    EClientSocket.h \
    EClient.h \
    Contract.h \
    CommonDefs.h \
    CommissionReport.h

