#file(GLOB_RECURSE SRC_LIST  *.cxx)
#\

file(GLOB_RECURSE SRC_LIST "*.cpp")

#add_subdirectory(fq)
#aux_source_directory(fq SRC_LIST)
include_directories(.)

find_package(Boost 1.51)

add_library(${PROJECT_NAME} ${SRC_LIST})

