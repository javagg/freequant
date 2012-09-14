#file(GLOB_RECURSE SRC_LIST  *.cxx)
#\
add_subdirectory(indicators)
add_subdirectory(marketdata)
add_subdirectory(server)
add_subdirectory(strategy)
add_subdirectory(trade)
add_subdirectory(utils)

aux_source_directory(indicators SRC_LIST)
aux_source_directory(marketdata SRC_LIST)
aux_source_directory(server SRC_LIST)
aux_source_directory(strategy SRC_LIST)
aux_source_directory(trade SRC_LIST)
aux_source_directory(utils SRC_LIST)

