TEMPLATE = app
#CONFIG -= console
#CONFIG -= qt

SOURCES += \
    main.cpp

#win32 {
#    BOOST_INC = $$(BOOST_HOME)
#    BOOST_LIB = $$(BOOST_HOME)/lib
#    QUICKFIX_INC = $$(QUICKFIX_HOME)/include
#    QUICKFIX_LIB = $$(QUICKFIX_HOME)/lib
#} unix {
#    BOOST_INC = /usr/include
#    BOOST_LIB = /usr/lib
#    QUICKFIX_INC = /usr/include
#    QUICKFIX_LIB = /usr/lib
#}

#INCLUDEPATH += $$BOOST_INC
#LIBS += -L$$BOOST_LIB -lm

INCLUDEPATH += $$PWD/../../src
DEPENDPATH += $$PWD/../../src
