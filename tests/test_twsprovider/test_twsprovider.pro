TEMPLATE = app
SOURCES += main.cpp

INCLUDEPATH += $$PWD/../../src
DEPENDPATH += $$PWD/../../src

LIBS += -lboost_system
LIBS += -L$$OUT_PWD/../../src/ -lfreequant
