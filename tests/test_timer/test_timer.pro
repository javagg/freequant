TEMPLATE = app
SOURCES += main.cpp

include(../../misc/common.pri)

win32 {
    LIBS += -L$$OUT_PWD/../../src/debug -lfreequant
} unix {
    LIBS += -L$$OUT_PWD/../../src -lfreequant
    LIBS += -L$$BOOST_LIB -lboost_system -lboost_thread -lboost_date_time
}
