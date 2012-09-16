project(freequant)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

find_package(Boost REQUIRED COMPONENTS date_time system thread)
find_package(CURL REQUIRED)
find_package(QuickFIX REQUIRED)

set(TWS_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/vendors/tws)
set(CTP_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/vendors/ctp)

if(WIN32)
    set(CTP_LIBRARY_DIRS ${CMAKE_CURRENT_LIST_DIR}/vendors/ctp/api/trade/win/lib ${CMAKE_CURRENT_LIST_DIR}/vendors/ctp/api/risk/lib)
    set(CTP_LIBRARIES thostmduserapi thosttraderapi riskuserapi)
else(UNIX)
    set(CTP_LIBRARY_DIRS ${CMAKE_CURRENT_LIST_DIR}/vendors/ctp/api/trade/linux64/lib)
    set(CTP_LIBRARIES thostmduserapi thosttraderapi)
endif()

include_directories(${Boost_INCLUDE_DIRS} ${CURL_INCLUDE_DIRS} ${QuickFIX_INCLUDE_DIRS} ${TWS_INCLUDE_DIRS} ${CTP_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_LIST_DIR}/src)

set(CTP_LIBRARIES thostmduserapi thosttraderapi)

find_library(CTP_LIBRARIES NAMES thostmduserapi thosttraderapi PATHS ${CTP_LIBRARY_DIRS})

link_directories(${CTP_LIBRARY_DIRS})

message(${CTP_LIBRARY_DIRS})

add_subdirectory(src lib)
add_subdirectory(examples)
add_subdirectory(server)

