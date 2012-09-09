TEMPLATE = app
SOURCES += main.cpp

win32 {
    CURL_INC = $$quote($$(CURL_HOME))/include
    CURL_LIB = $$quote($$(CURL_HOME))/lib/release
    CTP_INC = $$PWD/../../vendors/ctp/trade/win/public


    INCLUDEPATH += $$PWD/../../src
    DEPENDPATH += $$PWD/../../src

    INCLUDEPATH += $$CURL_INC
    LIBS += -L$$OUT_PWD/../../src/release/ -lfreequant
    LIBS += -L$$PWD/../../vendors/ctp/trade/win/lib/ -lthostmduserapi

    LIBS += -lboost_system
}


INCLUDEPATH += $$PWD/../../src
DEPENDPATH += $$PWD/../../src

LIBS += -lboost_system
unix:LIBS += -L$$OUT_PWD/../../src/ -lfreequant
