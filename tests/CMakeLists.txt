add_subdirectory(test_provider)
add_subdirectory(test_timer)
add_subdirectory(test_strategy)

file(GLOB SOURCES *.cpp)

add_executable(fqtest ${SOURCES})
target_link_libraries(fqtest ${Boost_LIBRARIES} ${PROJECT_NAME})

