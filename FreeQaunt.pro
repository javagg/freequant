#-------------------------------------------------
#
# Project created by QtCreator 2012-08-29T16:50:49
#
#-------------------------------------------------

QT       -= core gui

TARGET = FreeQaunt
TEMPLATE = lib

DEFINES += FREEQAUNT_LIBRARY

SOURCES += freeqaunt.cpp \
    datetime.cpp \
    timeseries.cpp \
    transaction.cpp \
    timeseries.cpp \
    strategy.cpp \
    stock.cpp \
    signal.cpp \
    rule.cpp \
    portfolio.cpp \
    parameter.cpp \
    order_book.cpp \
    order.cpp \
    instrument.cpp \
    indicator.cpp \
    freeqaunt.cpp \
    datetime.cpp \
    currency.cpp \
    account.cpp

HEADERS += freeqaunt.h \
    datetime.h \
    timeseries.h \
    transaction.h \
    timeseries.h \
    strategy.h \
    stock.h \
    signal.h \
    rule.h \
    portfolio.h \
    parameter.h \
    order_book.h \
    order.h \
    instrument.h \
    indicator.h \
    freeqaunt.h \
    datetime.h \
    currency.h \
    account.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE0F39D35
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = FreeQaunt.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
