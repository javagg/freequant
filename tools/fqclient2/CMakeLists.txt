find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
set(QT_USE_QTUITOOLS TRUE)

#FILE(GLOB MarkTracker_SOURCES *.cpp)
#FILE(GLOB MarkTracker_HEADERS *.hpp)
#FILE(GLOB MarkTracker_UI *.ui)

set(SOURCES main.cpp mainwindow.cpp commondialog.cpp)
set(HEADERS mainwindow.h commondialog.h)
set(UIS mainwindow.ui commondialog.ui)
qt4_add_resources(RCS forms.qrc)
qt4_wrap_ui(UIS_HEADERS ${UIS})
qt4_wrap_cpp(MOC_HEADERS ${HEADERS})

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(fqclient2 ${SOURCES} ${UIS_HEADERS} ${MOC_HEADERS})
target_link_libraries(fqclient2 ${QT_LIBRARIES} ${CTP_LIBRARIES} ${PROJECT_NAME} ${WS2_32})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.fix ${CMAKE_CURRENT_BINARY_DIR}/config.fix COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/FIX44.xml ${CMAKE_CURRENT_BINARY_DIR}/FIX44.xml COPYONLY)
