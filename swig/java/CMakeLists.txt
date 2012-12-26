include_directories(${JAVA_INCLUDE_PATH} ${JNI_INCLUDE_DIRS})

set(_package_name "org.freequant")
string(REPLACE "." "/" _package_dir ${_package_name})
set(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR}/${_package_dir})
set(CMAKE_SWIG_FLAGS "-package" ${_package_name})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CtpMdTester.java ${CMAKE_SWIG_OUTDIR}/CtpMdTester.java COPYONLY)

set(WRAPPER_FILES java.i)
set_source_files_properties(${WRAPPER_FILES} PROPERTIES CPLUSPLUS ON)

swig_add_module(freequant-java java ${WRAPPER_FILES})
swig_link_libraries(freequant-java ${JNI_LIBRARIES} ${PROJECT_NAME})

#add_custom_target(freequant_jar ALL DEPENDS ${JAR_FILE})

set(SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/build)
file(MAKE_DIRECTORY ${SOURCE_DIR})
file(MAKE_DIRECTORY ${BINARY_DIR})

set(JAVA_SOURCES ${CMAKE_CURRENT_BINARY_DIR}/org/freequant/*.java)

foreach(_file ${CTP_SHAREDLIBFILES})
    file(COPY ${_file} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    get_filename_component(_rfile ${_file} NAME)
    list(APPEND _ctpfiles ${_rfile})
endforeach()
get_target_property(_target_location freequant-java LOCATION)
get_filename_component(_target_name ${_target_location} NAME)

add_custom_command(OUTPUT freequant_java_jar
    COMMENT "Creating jar file..."
    COMMAND ${Java_JAVAC_EXECUTABLE} -d ${BINARY_DIR} ${JAVA_SOURCES}
    COMMAND ${Java_JAR_EXECUTABLE} cf ${CMAKE_CURRENT_BINARY_DIR}/freequant.jar -C ${BINARY_DIR} org
    COMMAND ${Java_JAR_EXECUTABLE} uf ${CMAKE_CURRENT_BINARY_DIR}/freequant.jar ${_ctpfiles} ${_target_name}

#    COMMAND ${Java_JAVADOC_EXECUTABLE} -quiet -d ${JAVA_BINARY_DIRECTORY}/javadoc -sourcepath ${JAVA_SOURCE_DIRECTORY} org.itk.simple
#    COMMAND ${Java_JAR_EXECUTABLE} cf ${CMAKE_CURRENT_BINARY_DIR}/${JAVADOC_FILE} -C ${JAVA_BINARY_DIRECTORY}/javadoc org
#    COMMAND ${Java_JAR_EXECUTABLE} cf ${CMAKE_CURRENT_BINARY_DIR}/${JAVA_SOURCES} org
   DEPENDS freequant-java
)

add_custom_target(do_trofiles ALL DEPENDS freequant_java_jar)

find_package(Maven)
if(MAVEN_EXECUTABLE)
    add_custom_command(OUTPUT freequant_java_install
        COMMENT "install jar file..."
        COMMAND ${MAVEN_EXECUTABLE} install:install-file -Dfile=${CMAKE_CURRENT_BINARY_DIR}/freequant.jar -DgroupId=${_package_name} -DartifactId=freequant -Dversion=0.0.1 -Dpackaging=jar
        DEPENDS freequant_java_jar
    )
    add_custom_target(install_jar ALL DEPENDS do_trofiles freequant_java_install)
endif()
