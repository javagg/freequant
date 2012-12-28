include_directories(${JAVA_INCLUDE_PATH} ${JNI_INCLUDE_DIRS})

set(_package_name "org.freequant")

set(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR})
set (CMAKE_SWIG_FLAGS "")

set(WRAPPER_FILES ctp.i)
set_source_files_properties(${WRAPPER_FILES} PROPERTIES CPLUSPLUS ON)

swig_add_module(ctp java ${WRAPPER_FILES})
#swig_link_libraries(freequant-csharp1 ${PROKECT_NAME})
swig_add_module(ctpcs csharp ${WRAPPER_FILES})

