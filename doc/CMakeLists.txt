add_custom_target(doc ALL ${DOXYGEN_EXECUTABLE} ${PROJECT_SOURCE_DIR}/doc/Doxyfile COMMENT "Generating API documentation with Doxygen" VERBATIM)
 