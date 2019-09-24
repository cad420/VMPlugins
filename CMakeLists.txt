cmake_minimum_required(VERSION 2.7)
set(CMAKE_CXX_VERSION 14)
project(vmplugins)

file(GLOB_RECURSE COMMON_SOURCES "visualman/*.cc")
include_directories("${CMAKE_SOURCE_DIR}/visualman")

add_subdirectory(src)
