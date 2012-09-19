project(freequant)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

#Find external dependencies
find_package(Boost REQUIRED COMPONENTS date_time system thread)
find_package(CURL REQUIRED)
find_package(QuickFIX REQUIRED)
find_package(Doxygen)
if(DOXYGEN_FOUND)
    add_subdirectory(doc)
endif()

# Find in-the-source dependencies
set(TWS_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/vendors/tws)
set(CTP_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/vendors/ctp)

if(WIN32)
    set(CTP_LIBRARY_DIRS ${CMAKE_CURRENT_LIST_DIR}/vendors/ctp/api/trade/win/lib ${CMAKE_CURRENT_LIST_DIR}/vendors/ctp/api/risk/lib)
    set(CTP_LIBRARIES thostmduserapi thosttraderapi riskuserapi)
else(UNIX)
    set(CTP_LIBRARY_DIRS ${CMAKE_CURRENT_LIST_DIR}/vendors/ctp/api/trade/linux64/lib)
    set(CTP_LIBRARIES thostmduserapi thosttraderapi)
endif()

include_directories(${Boost_INCLUDE_DIRS} ${CURL_INCLUDE_DIRS} ${QUICKFIX_INCLUDE_DIRS} ${TWS_INCLUDE_DIRS} ${CTP_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_LIST_DIR}/src)

link_directories(${Boost_LIBRARY_DIRS} ${CTP_LIBRARY_DIRS})

add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(server)

configure_file(${PROJECT_SOURCE_DIR}/config.h.cmake ${PROJECT_BINARY_DIR}/config.h)
include_directories(${PROJECT_BINARY_DIR})

option(BUILD_TESTS "Build tests." TRUE)
if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

