add_executable(server main.cpp)
target_link_libraries(server ${PROJECT_NAME} ${QUICKFIX_LIBRARIES} ${WS2_32} ${Boost_LIBRARIES})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.fix ${PROJECT_BINARY_DIR}/bin/config.fix COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/FIX44.xml ${PROJECT_BINARY_DIR}/bin/FIX44.xml COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/FIX42.xml ${PROJECT_BINARY_DIR}/bin/FIX42.xml COPYONLY)

add_executable(fixgw FixGateway.cpp)
target_link_libraries(fixgw ${PROJECT_NAME} ${QUICKFIX_LIBRARIES} ${Boost_LIBRARIES})
