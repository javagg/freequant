include_directories(${RUBY_INCLUDE_DIRS})

set(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR})
set (CMAKE_SWIG_FLAGS "")

set(WRAPPER_FILES freequant.i)
set_source_files_properties(${WRAPPER_FILES} PROPERTIES CPLUSPLUS ON)
set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/freequantRUBY_wrap.cxx  PROPERTIES COMPILE_FLAGS "-w")

swig_add_module(freequant-ruby ruby ${WRAPPER_FILES})
swig_link_libraries(freequant-ruby ${RUBY_LIBRARIES} ${PROJECT_NAME})

#install(FILES "${CMAKE_CURRENT_BINARY_DIR}/libfreequant-ruby.so" DESTINATION lib/ruby)
