TEMPLATE = app
SOURCES += main.cpp

INCLUDEPATH += $$PWD/../../src
DEPENDPATH += $$PWD/../../src

LIBS += -L$$PWD/../../src/fq/marketdata/ctp/api/trade/linux64/lib/ -lthostmduserapi

LIBS += -L$$OUT_PWD/../../src/ -lfreequant
LIBS += -lboost_system
