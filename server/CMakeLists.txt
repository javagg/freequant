add_executable(server main.cpp)

if(WIN32)
    set(WS2_32 ws2_32)
endif()
target_link_libraries(server ${PROJECT_NAME} ${QUICKFIX_LIBRARIES} ${WS2_32})
