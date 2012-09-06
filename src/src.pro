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
    currency.cpp \
    account.cpp \
    exchange.cpp \
    market.cpp \
    position.cpp \
    fq/marketdata/provider.cpp \
    fq/marketdata/ctp/ctpprovider.cpp \
    fq/marketdata/csv/csvprovider.cpp \
    fq/indicators/indicator.cpp \
    fq/bar.cpp

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
    currency.h \
    account.h \
    exchange.h \
    market.h \
    position.h \
    fq/marketdata/provider.h \
    fq/marketdata/ctp/ctpprovider.h \
    fq/marketdata/csv/csvprovider.h \
    fq/indicators/indicator.h \
    fq/bar.h

*-g++* {
#    QMAKE_CXXFLAGS += -std=c++11
}

win32 {
    BOOST_INC = $$(BOOST_HOME)
    BOOST_LIB = $$(BOOST_HOME)/lib
    QUICKFIX_INC = $$(QUICKFIX_HOME)/include
    QUICKFIX_LIB = $$(QUICKFIX_HOME)/lib
} unix {
    BOOST_INC = /usr/include
    BOOST_LIB = /usr/lib
    QUICKFIX_INC = /usr/include
    QUICKFIX_LIB = /usr/lib
}

INCLUDEPATH += $$BOOST_INC
LIBS += -L$$BOOST_LIB -lm

#QMAKE_CXXFLAGS += -Wc++11-extensions

