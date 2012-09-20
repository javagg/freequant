cmake_minimum_required(VERSION 2.6)
project(fqclient)

set(CMAKE_AUTOMOC ON)
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

set(SOURCES main.cpp mainwindow.cpp)
set(HEADERS mainwindow.h)
set(UIS mainwindow.ui)

qt4_wrap_ui(UIS_HEADERS ${UIS})
qt4_automoc(${SOURCES})

include_directories(${PROJECT_BINARY_DIR})

add_executable(${PROJECT_NAME} ${SOURCES} ${UIS_HEADERS} ${MOC_HEADERS})

target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES})

add_definitions(-Wall)
