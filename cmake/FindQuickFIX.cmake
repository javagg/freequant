find_path(QuickFIX_INCLUDE_DIR quickfix/FixValues.h HINTS /usr/include)
find_library(QuickFIX_LIBRARY NAMES quickfix libquickfix HINTS /usr/lib)

set(QuickFIX_LIBRARIES ${QuickFIX_LIBRARY})
set(QuickFIX_INCLUDE_DIRS ${QuickFIX_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(QuickFIX  DEFAULT_MSG QUICKFIX_LIBRARY QUICKFIX_INCLUDE_DIR)
mark_as_advanced(QuickFIX_INCLUDE_DIR QuickFIX_LIBRARY)


