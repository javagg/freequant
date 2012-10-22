find_path(QUICKFIX_INCLUDE_DIR quickfix/FixValues.h HINTS /usr/include $ENV{QUICKFIX_HOME}/include)

if(MSVC)
    if(CMAKE_BUILD_TYPE STREQUAL Debug)
        find_library(QUICKFIX_LIBRARY NAMES quickfixd HINTS /usr/lib $ENV{QUICKFIX_HOME}/lib/Debug)
    elseif(CMAKE_BUILD_TYPE STREQUAL Release)
        find_library(QUICKFIX_LIBRARY NAMES quickfix HINTS /usr/lib $ENV{QUICKFIX_HOME}/lib/Release)
    endif()
else()
    find_library(QUICKFIX_LIBRARY NAMES libquickfix HINTS /usr/lib)
endif()

set(QUICKFIX_LIBRARIES ${QUICKFIX_LIBRARY})
set(QUICKFIX_INCLUDE_DIRS ${QUICKFIX_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(QUICKFIX DEFAULT_MSG QUICKFIX_LIBRARY QUICKFIX_INCLUDE_DIR)
mark_as_advanced(QUICKFIX_INCLUDE_DIR QUICKFIX_LIBRARY)

