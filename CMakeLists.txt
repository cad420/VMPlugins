cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_VERSION 14)
project(vmplugins)

include(scripts/external.cmake)
#include_directories("${CMAKE_SOURCE_DIR}/extension")

vm_external_module(
  GIT_REPOSITORY https://github.com/cad420/VMCore.git
  GIT_TAG        master
)

add_subdirectory(src)
