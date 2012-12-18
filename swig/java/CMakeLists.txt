include_directories(${JNI_INCLUDE_DIRS})

set(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR}/org/freequant)
set(CMAKE_SWIG_FLAGS "-package" "org.freequant")

set(WRAPPER_FILES freequant.i)
set_source_files_properties(${WRAPPER_FILES} PROPERTIES CPLUSPLUS ON)

swig_add_module(freequant-java java ${WRAPPER_FILES})
swig_link_libraries(freequant-java ${JNI_LIBRARIES} ${PROJECT_NAME})

add_custom_target(freequant_jar ALL DEPENDS ${JAR_FILE})
set(JAVA_SOURCES ${CMAKE_CURRENT_BINARY_DIR}/org/freequant/*.java)

#add_custom_command(OUTPUT ${JAR_FILE}
#    COMMENT "Creating jar file..."
#    COMMAND ${Java_JAVAC_EXECUTABLE} -d ${JAVA_BINARY_DIRECTORY} ${JAVA_SOURCE_CODE}
#    COMMAND ${Java_JAR_EXECUTABLE} cf ${CMAKE_CURRENT_BINARY_DIR}/${JAR_FILE} -C ${JAVA_BINARY_DIRECTORY} org
#    COMMAND ${Java_JAVADOC_EXECUTABLE} -quiet -d ${JAVA_BINARY_DIRECTORY}/javadoc -sourcepath ${JAVA_SOURCE_DIRECTORY} org.itk.simple
#    COMMAND ${Java_JAR_EXECUTABLE} cf ${CMAKE_CURRENT_BINARY_DIR}/${JAVADOC_FILE} -C ${JAVA_BINARY_DIRECTORY}/javadoc org
#    COMMAND ${Java_JAR_EXECUTABLE} cf ${CMAKE_CURRENT_BINARY_DIR}/${JAVA_SOURCE_FILE} org
#    DEPENDS ${SWIG_MODULE_SimpleITKJava_TARGET_NAME}
#    )

  # Get the location of the extension directory
  string(REGEX REPLACE "include" "jre/lib/ext" JAVA_EXTENSION_DIR ${JAVA_INCLUDE_PATH})

  # TODO: add new target to install simpleitk java
  # Add the install target
  # install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${JAR_FILE} DESTINATION ${JAVA_EXTENSION_DIR})
