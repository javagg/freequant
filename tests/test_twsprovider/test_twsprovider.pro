TEMPLATE = app
SOURCES += main.cpp

INCLUDEPATH += $$PWD/../../src
DEPENDPATH += $$PWD/../../src

LIBS += -lboost_system
unix:LIBS += -L$$OUT_PWD/../../src/ -lfreequant

