set(CSharp_FOUND FALSE)

find_program(CSC_v1_EXECUTABLE
    NAMES csc
    HINTS
    [HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\.NETFramework;InstallRoot]/v1.1.4322
)

find_program(CSC_v2_EXECUTABLE csc
    HINTS
    [HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\.NETFramework;InstallRoot]/v2.0.50727/
)

find_program(CSC_v3_EXECUTABLE csc
    HINTS
    [HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\.NETFramework;InstallRoot]/v3.5/
)

find_program(CSC_v4_EXECUTABLE csc
    HINTS
    [HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\.NETFramework;InstallRoot]/v4.0.30319/
)

if(CSC_v1_EXECUTABLE OR CSC_v2_EXECUTABLE OR CSC_v3_EXECUTABLE OR CSC_v4_EXECUTABLE)
    set(CSharp_FOUND TRUE)
    if(CSC_v4_EXECUTABLE)
        set(CSC_EXECUTABLE ${CSC_v4_EXECUTABLE})
    elseif(CSC_v3_EXECUTABLE)
        set(CSC_EXECUTABLE ${CSC_v3_EXECUTABLE})
    elseif(CSC_v2_EXECUTABLE)
        set(CSC_EXECUTABLE ${CSC_v2_EXECUTABLE})
    elseif(CSC_v1_EXECUTABLE)
        set(CSC_EXECUTABLE ${CSC_v1_EXECUTABLE})
    endif()
endif()

mark_as_advanced(CSC_v1_EXECUTABLE CSC_v2_EXECUTABLE CSC_v3_EXECUTABLE CSC_v4_EXECUTABLE)

