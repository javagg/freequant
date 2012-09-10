TEMPLATE = app
SOURCES += main.cpp

include(../../misc/common.pri)

win32 {
    LIBS += -L$$OUT_PWD/../../src/debug -lfreequant
}
