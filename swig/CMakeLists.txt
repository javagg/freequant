find_package(SWIG)
if(SWIG_FOUND)
    include(${SWIG_USE_FILE})
    find_package(Java)
    find_package(JNI)
    find_package(Ruby)
    find_package(PythonLibs)
    find_package(R)
    #find_package(CSharp)
    find_package(Mono)
    # use $ENV{LUA_DIR}
    #find_package(Lua51)
    #find_package(PerlLibs)
    find_package(TCL)
    find_package(Octave)

    if(JNI_FOUND)
        add_subdirectory(java)
    endif()

    if(RUBY_FOUND)
        add_subdirectory(ruby)
    endif(RUBY_FOUND)

    if(R_FOUND)
        add_subdirectory(R)
    endif(R_FOUND)

    if(PYTHONLIBS_FOUND)
        add_subdirectory(python)
    endif(PYTHONLIBS_FOUND)

    if(CSharp_FOUND OR MONO_FOUND)
        add_subdirectory(csharp)
    endif()

    if(LUA51_FOUND)
        add_subdirectory(lua)
    endif(LUA51_FOUND)

    if(TCL_FOUND)
        add_subdirectory(tcl)
    endif(TCL_FOUND)

    if(PERLLIBS_FOUND)
        add_subdirectory(perl)
    endif(PERLLIBS_FOUND)

    if(OCTAVE_FOUND)
        add_subdirectory(octave)
    endif(OCTAVE_FOUND)

endif()



