add_executable(fixtradeclient tradeclient.cpp Application.cpp)
target_link_libraries(fixtradeclient ${QUICKFIX_LIBRARIES})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_executable(SimpleClient SimpleClient.cpp)
target_link_libraries(SimpleClient ${Boost_LIBRARIES})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_executable(SimpleServer SimpleServer.cpp)
target_link_libraries(SimpleServer ${Boost_LIBRARIES})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_executable(TimeServer TimeServer.cpp)
target_link_libraries(TimeServer ${Boost_LIBRARIES})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_executable(TimeClient TimeClient.cpp)
target_link_libraries(TimeClient ${Boost_LIBRARIES})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
