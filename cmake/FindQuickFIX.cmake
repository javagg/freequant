find_path(QUICKFIX_INCLUDE_DIR quickfix/FixValues.h HINTS /usr/include $ENV{QUICKFIX_HOME}/include)


if(${MSVC})
    if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
        set(LIB_NAMES quickfixd)
    else()
        set(LIB_NAMES quickfix)
    endif()
else()
    set(LIB_NAMES libquickfix)
endif()

find_library(QUICKFIX_LIBRARY NAMES ${LIB_NAMES} HINTS /usr/lib $ENV{QUICKFIX_HOME}/lib)

set(QUICKFIX_LIBRARIES ${QUICKFIX_LIBRARY})
set(QUICKFIX_INCLUDE_DIRS ${QUICKFIX_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(QUICKFIX DEFAULT_MSG QUICKFIX_LIBRARY QUICKFIX_INCLUDE_DIR)
mark_as_advanced(QUICKFIX_INCLUDE_DIR QUICKFIX_LIBRARY)

