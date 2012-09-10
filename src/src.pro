#-------------------------------------------------
#
# Project created by QtCreator 2012-08-29T16:50:49
#
#-------------------------------------------------

TARGET = freequant
TEMPLATE = lib

CONFIG += debug_and_release staticlib

DEFINES += FREEQAUNT_LIBRARY

SOURCES += \
    fq/utils/datetime.cpp \
    transaction.cpp \
    fq/utils/timeseries.cpp \
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
    fq/marketdata/ctp/ctpprovider.cpp \
    fq/marketdata/csv/csvprovider.cpp \
    fq/indicators/indicator.cpp \
    fq/bar.cpp \
    fq/marketdata/bogus/bogusprovoder.cpp \
    fq/utils/timer.cpp \
    fq/marketdata/yahooprovider.cpp \
    fq/utils/httpclient.cpp \
    fq/utils/csvparser.cpp \
    fq/quote.cpp \
    fq/marketdata/twsprovider.cpp \
    fq/marketdata/tws/EPosixClientSocket.cpp \
    fq/marketdata/tws/EClientSocketBase.cpp \
    fq/trade/ctpprovider.cpp

HEADERS += \
    fq/utils/datetime.h \
    transaction.h \
    fq/utils/timeseries.h \
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
    fq/utils/csvparser.h \
    fq/quote.h \
    fq/marketdata/twsprovider.h \
    fq/marketdata/tws/EPosixClientSocketPlatform.h \
    fq/marketdata/tws/EPosixClientSocket.h \
    fq/trade/provider.h \
    fq/trade/ctpprovider.h


include(../misc/common.pri)

