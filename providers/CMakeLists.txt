if(BUILD_CTP_PROVIDER)
    add_subdirectory(ctp)
endif()

if(BUILD_CTPSSE_PROVIDER)
    add_subdirectory(ctpsse)
endif()

if(BUILD_FIX_PROVIDER)
    add_subdirectory(fix)
endif()

if(BUILD_TWS_PROVIDER)
    add_subdirectory(tws)
endif()
