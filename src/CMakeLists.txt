#file(GLOB_RECURSE HEADERS *.h *.hpp)
#file(GLOB_RECURSE SOURCES *.cpp)
#file(GLOB_RECURSE TWS_SRC ${PROJECT_SOURCE_DIR}/vendors/tws/*.cpp)

#file(GLOB HEADERS
#    freequant/*.h
#    freequant/data/*.h
#    freequant/detail/*.h
#    freequant/experiment/*.h
#    freequant/fix/*.cpp
#    freequant/indicators/*.h
#    freequant/marketdata/*.cpp
#    freequant/server/*.cpp
#    freequant/strategy/*.cpp
#    freequant/trade/*.cpp
#    freequant/utils/*.cpp
#}

file(GLOB SOURCES
    freequant/*.cpp
    freequant/data/*.cpp
    freequant/detail/*.cpp
    freequant/experiment/*.cpp
    freequant/fix/*.cpp
    freequant/indicators/*.cpp
    freequant/marketdata/*.cpp
    freequant/server/*.cpp
    freequant/strategy/*.cpp
    freequant/trade/*.cpp
    freequant/utils/*.cpp
)

if(BUILD_CTP_PROVIDER)
    file(GLOB_RECURSE _ctp_providers_src freequant/providers/ctp/*.cpp)
    list(APPEND SOURCES ${_ctp_providers_src})
endif(BUILD_CTP_PROVIDER)

if(BUILD_CTPSSE_PROVIDER)
    if(WIN32)
        include_directories(freequant/providers/ctpsse/lib/win)
    elseif(UNIX)
        include_directories(freequant/providers/ctpsse/lib/linux64)
    endif()
    file(GLOB_RECURSE _ctpsse_providers_src freequant/providers/ctpsse/*.cpp)
    list(APPEND SOURCES ${_ctpsse_providers_src})
endif()

if(BUILD_FIX_PROVIDER)
    file(GLOB_RECURSE _fix_providers_src freequant/providers/fix/*.cpp)
    list(APPEND SOURCES ${_fix_providers_src})
endif()

if(BUILD_TWS_PROVIDER)
    file(GLOB_RECURSE _tws_providers_src freequant/providers/tws/*.cpp)
    list(APPEND SOURCES ${_tws_providers_src})
    include_directories(freequant/providers/tws/Shared)
    add_definitions(-D_AFXDLL -DIB_USE_STD_STRING)
endif()

add_library(${PROJECT_NAME} ${SOURCES} ${TWS_SRC})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${CURL_LIBRARIES} ${QUICKFIX_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${CTP_LIBRARIES})
add_definitions(-D_AFXDLL -DIB_USE_STD_STRING -DBOOST_NETWORK_NO_LIB)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION "1.0" SOVERSION "1")

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(DIRECTORY freequant DESTINATION include FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")
