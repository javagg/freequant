function(_QT5_QUERY_QMAKE VAR RESULT)
  execute_process(COMMAND "${QT_QMAKE_EXECUTABLE}" -query ${VAR}
    RESULT_VARIABLE return_code
    OUTPUT_VARIABLE output
    OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_STRIP_TRAILING_WHITESPACE)
  if(NOT return_code)
    file(TO_CMAKE_PATH "${output}" output)
    set(${RESULT} ${output} PARENT_SCOPE)
  endif()
endfunction()

find_program(QT_QMAKE_EXECUTABLE NAMES qmake PATHS ENV QTDIR
  PATH_SUFFIXES bin
  DOC "The qmake executable for the Qt installation to use"
)

if(QT_QMAKE_EXECUTABLE)
  _qt5_query_qmake(QT_INSTALL_LIBS _qt_lib_dir)
  if(_qt_lib_dir)
    list(APPEND CMAKE_MODULE_PATH ${_qt_lib_dir}/cmake)
    include(Qt5Core/Qt5CoreConfig)
  endif()
endif()
