add_subdirectory(test_provider)
add_subdirectory(test_timer)
add_subdirectory(test_strategy)
add_subdirectory(swig)

file(GLOB SOURCES *.cpp)

#add_executable(fqtest ${SOURCES})
#target_link_libraries(fqtest ${Boost_LIBRARIES} ${PROJECT_NAME})

#file(GLOB DATA data/*.*)
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
