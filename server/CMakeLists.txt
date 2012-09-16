add_executable(server main.cpp)

target_link_libraries(server ${PROJECT_NAME} ${QuickFIX_LIBRARIES})
