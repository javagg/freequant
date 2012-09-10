win32 {
    BOOST_INC = $$quote($$(BOOST_HOME))
    BOOST_LIB = $$quote($$(BOOST_HOME))/lib
    QUICKFIX_INC = $$quote($$(QUICKFIX_HOME))/include
    QUICKFIX_LIB = $$quote($$(QUICKFIX_HOME))/lib

    CURL_INC = $$quote($$(CURL_HOME))/include
    CURL_LIB = $$quote($$(CURL_HOME))/lib/release

    BOOST_LIB_SUFFIX = -vc100-mt-1_51

    # for tws
    DEFINES += _AFXDLL IB_USE_STD_STRING
    DEFINES -= UNICODE
    TWS_INC = $$PWD/../vendors/tws/Shared

    LIBS += -L$$PWD/../vendors/ctp/trade/win/lib -lthostmduserapi
    LIBS += -L$$CURL_LIB -lcurllib
    LIBS += -L$$BOOST_LIB
    LIBS += -L$$OUT_PWD/src/debug -lfreequant
#    LIBS += -lboost_system$$BOOST_LIB_SUFFIX -lboost_thread-vc100-mt-gd-1_51
}
unix {
    BOOST_INC = /usr/include
    BOOST_LIB = /usr/lib
    QUICKFIX_INC = /usr/include
    QUICKFIX_LIB = /usr/lib

    # for tws
    DEFINES += IB_USE_STD_STRING
    TWS_INC = $$PWD/../vendors/tws/Shared

    LIBS += -L$$BOOST_LIB -lboost_system -lboost_thread -lcurl
    LIBS += -L$$PWD/fq/marketdata/ctp/api/trade/linux64/lib -lthostmduserapi
#    LIBS += -L$$BOOST_LIB -lboost_system$$BOOST_LIB_SUFFIX -lboost_thread$$BOOST_LIB_SUFFIX
}

INCLUDEPATH += $$BOOST_INC $$CURL_INC $$QUICKFIX_INC $$TWS_INC $$PWD/../src
DEPENDPATH += $$PWD/../src
