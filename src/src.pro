#-------------------------------------------------
#
# Project created by QtCreator 2012-08-29T16:50:49
#
#-------------------------------------------------

FQ_ROOT = $${PWD}/..

TARGET = freequant
TEMPLATE = lib

CONFIG += debug_and_release staticlib

DEFINES += FREEQAUNT_LIBRARY

SOURCES += \
    fq/utils/datetime.cpp \
    fq/utils/timeseries.cpp \
    fq/marketdata/ctp/ctpprovider.cpp \
    fq/marketdata/csv/csvprovider.cpp \
    fq/indicators/indicator.cpp \
    fq/marketdata/bar.cpp \
    fq/marketdata/bogus/bogusprovoder.cpp \
    fq/utils/timer.cpp \
    fq/marketdata/yahooprovider.cpp \
    fq/utils/httpclient.cpp \
    fq/utils/csvparser.cpp \
    fq/marketdata/quote.cpp \
    fq/marketdata/twsprovider.cpp \
    fq/marketdata/tws/EPosixClientSocket.cpp \
    fq/marketdata/tws/EClientSocketBase.cpp \
    fq/trade/ctptradeprovider.cpp \
    fq/trade/fixtradeprovider.cpp \
    fq/strategy/strategy.cpp \
    fq/strategy/transaction.cpp \
    fq/strategy/stock.cpp \
    fq/strategy/rule.cpp \
    fq/strategy/position.cpp \
    fq/strategy/portfolio.cpp \
    fq/strategy/parameter.cpp \
    fq/strategy/orderbook.cpp \
    fq/strategy/order.cpp \
    fq/strategy/instrument.cpp \
    fq/strategy/exchange.cpp \
    fq/strategy/currency.cpp \
    fq/strategy/account.cpp

HEADERS += \
    fq/utils/datetime.h \
    fq/utils/timeseries.h \
    fq/marketdata/provider.h \
    fq/marketdata/ctp/ctpprovider.h \
    fq/marketdata/csv/csvprovider.h \
    fq/indicators/indicator.h \
    fq/marketdata/bar.h \
    fq/marketdata/bogus/bogusprovoder.h \
    fq/utils/timer.h \
    fq/marketdata/yahooprovider.h \
    fq/utils/httpclient.h \
    fq/utils/csvparser.h \
    fq/marketdata/quote.h \
    fq/marketdata/twsprovider.h \
    fq/marketdata/tws/EPosixClientSocketPlatform.h \
    fq/marketdata/tws/EPosixClientSocket.h \
    fq/trade/tradeprovider.h \
    fq/trade/ctptradeprovider.h \
    fq/trade/fixtradeprovider.h \
    fq/strategy/strategy.h \
    fq/strategy/transaction.h \
    fq/strategy/stock.h \
    fq/strategy/rule.h \
    fq/strategy/position.h \
    fq/strategy/portfolio.h \
    fq/strategy/parameter.h \
    fq/strategy/orderbook.h \
    fq/strategy/order.h \
    fq/strategy/instrument.h \
    fq/strategy/exchange.h \
    fq/strategy/currency.h \
    fq/strategy/account.h


include(../misc/common.pri)

