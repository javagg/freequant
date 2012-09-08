TEMPLATE = app
SOURCES += main.cpp

INCLUDEPATH += $$PWD/../../src
DEPENDPATH += $$PWD/../../src

LIBS += -L$$OUT_PWD/../../src/ -lfreequant -lboost_system
