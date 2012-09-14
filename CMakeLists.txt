project(freequant)

cmake_minimum_required(VERSION 2.6)

subdirs(src examples server tests)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

find_package(Boost)
IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()

find_package(CURL)
IF (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIR})
endif()


find_package(QuickFIX)
IF (QuickFIX_FOUND)
    include_directories(${QuickFIX_INCLUDE_DIR})
endif()

set(TWS_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/vendors/tws/Shared)
include_directories(${TWS_INCLUDE_DIR})

add_definitions(-D_AFX_DLL -DIB_USE_STD_STRING)
