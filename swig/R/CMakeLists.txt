include_directories(${R_INCLUDE_DIRS})
#set(CMAKE_SWIG_FLAGS ${CMAKE_SWIG_GLOBAL_FLAGS})
#set(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR})
#swig_add_module(freequant-r r freequant.i)
#set_source_files_properties(freequant.i PROPERTIES CPLUSPLUS ON)
#swig_link_libraries(freequant-r ${PROKECT_NAME} ${R_LIBRARIES})


set(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR})
set (CMAKE_SWIG_FLAGS "")

set(WRAPPER_FILES ../freequant.i)
set_source_files_properties(${WRAPPER_FILES} PROPERTIES CPLUSPLUS ON)
#set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/freequantRUBY_wrap.cxx  PROPERTIES COMPILE_FLAGS "-w")

swig_add_module(freequant-R R ${WRAPPER_FILES})
swig_link_libraries(freequant-R ${R_LIBRARIES} ${PROJECT_NAME})
