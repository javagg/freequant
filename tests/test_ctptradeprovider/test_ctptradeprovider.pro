TEMPLATE = app
SOURCES += main.cpp

include(../../misc/common.pri)


win32 {
    LIBS += -L$$OUT_PWD/../../src/debug -lfreequant
} unix {
    LIBS += -L$$OUT_PWD/../../src -lfreequant
    LIBS += -L$$PWD/../../vendors/ctp/trade/linux64/lib/ -lthosttraderapi
}

message($$OUT_PWD/../../src -lfreequant)
