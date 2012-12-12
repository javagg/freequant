include_directories(${LUA_INCLUDE_DIR})

set(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR})
set (CMAKE_SWIG_FLAGS "")

set(WRAPPER_FILES freequant.i)
set_source_files_properties(${WRAPPER_FILES} PROPERTIES CPLUSPLUS ON)

swig_add_module(freequant-lua lua ${WRAPPER_FILES})
swig_link_libraries(freequant-lua ${LUA_LIBRARIES} ${PROKECT_NAME})
