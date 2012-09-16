find_path(QUICKFIX_INCLUDE_DIR quickfix/FixValues.h HINTS /usr/include $ENV{QUICKFIX_HOME}/include)
find_library(QUICKFIX_LIBRARY NAMES quickfix libquickfix HINTS /usr/lib $ENV{QUICKFIX_HOME}/lib)

set(QUICKFIX_LIBRARIES ${QUICKFIX_LIBRARY})
set(QUICKFIX_INCLUDE_DIRS ${QUICKFIX_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(QUICKFIX DEFAULT_MSG QUICKFIX_LIBRARY QUICKFIX_INCLUDE_DIR)
mark_as_advanced(QUICKFIX_INCLUDE_DIR QUICKFIX_LIBRARY)

