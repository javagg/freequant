TEMPLATE = subdirs

SUBDIRS += \
    test_provider \
    test_timer \
    test_ctpprovider

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
#LIBS += -L$$BOOST_LIB


#win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/release/ -lfreeqaunt
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/debug/ -lfreeqaunt
#else:unix: LIBS += -L$$OUT_PWD/../src/ -lfreeqaunt

#INCLUDEPATH += $$PWD/../src
#DEPENDPATH += $$PWD/../src

#message($$INCLUDEPATH)
