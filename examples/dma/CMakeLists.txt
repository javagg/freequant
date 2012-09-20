add_executable(dma main.cpp)

#link_directories(${CTP_LIBRARY_DIRS})
#message(${CTP_LIBRARY_DIRS})
target_link_libraries(dma ${PROJECT_NAME} ${CTP_LIBRARIES})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

