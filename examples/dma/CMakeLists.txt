add_executable(dma main.cpp)
target_link_libraries(dma ${PROJECT_NAME} ${CTP_LIBRARIES})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

