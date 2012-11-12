if(WIN32)
    include_directories(lib/win)
elseif(UNIX)
    include_directories(lib/linux64)
endif()

file(GLOB SOURCES *.cpp)
add_library(freequant-ctpsse STATIC ${SOURCES})
target_link_libraries(freequant-ctpsse ${PROJECT_NAME})
