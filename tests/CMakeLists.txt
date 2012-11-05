add_subdirectory(test_provider)
add_subdirectory(test_timer)
add_subdirectory(test_strategy)

add_executable(fqtest BoostTestMain.cpp)
target_link_libraries(fqtest ${Boost_LIBRARIES})

