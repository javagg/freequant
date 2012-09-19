cmake_minimum_required(VERSION 2.6)
project(freequant)

set(CMAKE_VERBOSE_MAKEFILE true)
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
set(TWS_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/vendors/tws)
set(CTP_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/vendors/ctp)

if(WIN32)
    set(CTP_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/vendors/ctp/api/trade/win/lib ${PROJECT_SOURCE_DIR}/vendors/ctp/api/risk/lib)
elseif(UNIX)
    set(CTP_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/vendors/ctp/api/trade/linux64/lib)
endif()

find_library(CTP_MDUSER_LIBRARY NAMES thostmduserapi PATHS ${CTP_LIBRARY_DIR})
find_library(CTP_TRADE_LIBRARY NAMES thosttraderapi PATHS ${CTP_LIBRARY_DIR})
find_library(CTP_RISK_LIBRARY NAMES riskuserapi PATHS ${CTP_LIBRARY_DIR})

if(WIN32)
    if(CTP_MDUSER_LIBRARY AND CTP_TRADE_LIBRARY AND CTP_RISK_LIBRARY)
        set(CTP_LIBRARIES ${CTP_MDUSER_LIBRARY} ${CTP_TRADE_LIBRARY} ${CTP_RISK_LIBRARY})
    endif()
elseif(UNIX)
    if(CTP_MDUSER_LIBRARY AND CTP_TRADE_LIBRARY)
        set(CTP_LIBRARIES ${CTP_MDUSER_LIBRARY} ${CTP_TRADE_LIBRARY})
    endif()
endif()

include_directories(${Boost_INCLUDE_DIRS} ${CURL_INCLUDE_DIRS} ${QUICKFIX_INCLUDE_DIRS} ${TWS_INCLUDE_DIRS} ${CTP_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/src)

link_directories(${Boost_LIBRARY_DIRS})

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

