project(freequant)
cmake_minimum_required(VERSION 2.6)

subdirs(src examples server tests)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})
