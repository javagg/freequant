cmake_minimum_required (VERSION 2.6)

project (FREEQUANT)

add_subdirectory (examples)
add_subdirectory (src)

add_library(freequant src/fq/strategy.h)
