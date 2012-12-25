add_executable(pingserver PingServer.cpp)
target_link_libraries(pingserver ${PROJECT_NAME} ${QUICKFIX_LIBRARIES} ${WS2_32} ${Boost_LIBRARIES})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_executable(fixgw FixGateway.cpp)
target_link_libraries(fixgw ${PROJECT_NAME} ${QUICKFIX_LIBRARIES} ${Boost_LIBRARIES})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/server.conf ${PROJECT_BINARY_DIR}/bin/server.conf COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/FIX44.xml ${PROJECT_BINARY_DIR}/bin/FIX44.xml COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/FIX42.xml ${PROJECT_BINARY_DIR}/bin/FIX42.xml COPYONLY)
