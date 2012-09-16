find_path(QUICKFIX_INCLUDE_DIR quickfix/FixValues.h HINTS /usr/include $ENV{QUICKFIX_HOME}/include)
find_library(QUICKFIX_LIBRARY NAMES quickfix libquickfix HINTS /usr/lib $ENV{QUICKFIX_HOME}/lib)

set(QUICKFIX_LIBRARIES ${QUICKFIX_LIBRARY})
set(QUICKFIX_INCLUDE_DIRS ${QUICKFIX_INCLUDE_DIR})

# handle the QUIETLY and REQUIRED arguments and set ZLIB_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(QUICKFIX DEFAULT_MSG QUICKFIX_LIBRARY QUICKFIX_INCLUDE_DIR)
mark_as_advanced(QUICKFIX_INCLUDE_DIR QUICKFIX_LIBRARY)

