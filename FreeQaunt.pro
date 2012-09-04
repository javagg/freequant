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
    transaction.cpp \
    timeseries.cpp \
    strategy.cpp \
    stock.cpp \
    signal.cpp \
    rule.cpp \
    portfolio.cpp \
    parameter.cpp \
    orderbook.cpp \
    order.cpp \
    instrument.cpp \
    indicator.cpp \
    currency.cpp \
    account.cpp \
    exchange.cpp \
    market.cpp

HEADERS += freeqaunt.h \
    datetime.h \
    transaction.h \
    timeseries.h \
    strategy.h \
    stock.h \
    signal.h \
    rule.h \
    portfolio.h \
    parameter.h \
    orderbook.h \
    order.h \
    instrument.h \
    indicator.h \
    currency.h \
    account.h \
    exchange.h \
    market.h

*-g++* {
#    QMAKE_CXXFLAGS += -std=c++11
}

#QMAKE_CXXFLAGS += -Wc++11-extensions

#unix:!symbian {
#    maemo5 {
#        target.path = /opt/usr/lib
#    } else {
#        target.path = /usr/lib
#    }
#    INSTALLS += target
#}
