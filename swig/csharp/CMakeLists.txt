include(${MONO_USE_FILE})

set(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR})
set (CMAKE_SWIG_FLAGS "")

set(WRAPPER_FILES ../freequant.i)
set_source_files_properties(${WRAPPER_FILES} PROPERTIES CPLUSPLUS ON)

swig_add_module(freequant-csharp csharp ${WRAPPER_FILES})
swig_link_libraries(freequant-csharp ${PROKECT_NAME})

