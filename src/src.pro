#-------------------------------------------------
#
# Project created by QtCreator 2012-08-29T16:50:49
#
#-------------------------------------------------

TARGET = freequant
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
    fq/bar.cpp \
    fq/marketdata/bogus/bogusprovoder.cpp \
    fq/utils/timer.cpp \
    fq/marketdata/yahooprovider.cpp \
    fq/utils/httpclient.cpp \
    fq/utils/csvparser.cpp

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
    fq/bar.h \
    fq/marketdata/bogus/bogusprovoder.h \
    fq/utils/timer.h \
    fq/marketdata/yahooprovider.h \
    fq/utils/httpclient.h \
    fq/utils/csvparser.h

win32 {
    BOOST_INC = $$quote($$(BOOST_HOME))
    BOOST_LIB = $$quote($$(BOOST_HOME))
    BOOST_LIB = "c:/Program Files/boost/boost_1_51/lib"
    QUICKFIX_INC = $$(QUICKFIX_HOME)/include
    QUICKFIX_LIB = $$(QUICKFIX_HOME)/lib
    CURL_INC = $$quote($$(CURL_HOME))/include
    CURL_LIB = $$quote($$(CURL_HOME))/lib/release
}
unix {
    BOOST_INC = /usr/include
    BOOST_LIB = /usr/lib
    QUICKFIX_INC = /usr/include
    QUICKFIX_LIB = /usr/lib
}

INCLUDEPATH += $$BOOST_INC $$CURL_INC $$QUICKFIX_INC
LIBS += -L$$BOOST_LIB -lboost_system -lboost_thread -lcurl

