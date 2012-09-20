cmake_minimum_required(VERSION 2.6)
project(fqclient)

set(CMAKE_AUTOMOC ON)
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES})
add_definitions(-Wall)
