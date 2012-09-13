include($$PWD/../examples.pri)

SOURCES += main.cpp

LIBS += -L$$BOOST_LIB -lboost_thread
