find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
set(QT_USE_QTUITOOLS TRUE)

add_definitions(-DIB_USE_STD_STRING -D_AFXDLL)

set(SOURCES main.cpp mainwindow.cpp commondialog.cpp)
set(HEADERS mainwindow.h commondialog.h)
set(UIS mainwindow.ui commondialog.ui)
qt4_add_resources(RCS forms.qrc)
qt4_wrap_ui(UIS_HEADERS ${UIS})
qt4_wrap_cpp(MOC_HEADERS ${HEADERS})

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(fqclient2 ${SOURCES} ${UIS_HEADERS} ${MOC_HEADERS})
target_link_libraries(fqclient2 ${PROJECT_NAME} ${QT_LIBRARIES} ${WS2_32})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.fix ${CMAKE_CURRENT_BINARY_DIR}/config.fix COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/FIX44.xml ${CMAKE_CURRENT_BINARY_DIR}/FIX44.xml COPYONLY)
if(WIN32)
    file(COPY ${CTP_DLLS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()


