cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_VERSION 14)
project(vmplugins)

find_package(Git)
execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive)
include(scripts/external.cmake)
#include_directories("${CMAKE_SOURCE_DIR}/extension")

#add_subdirectory(VMCore)

vm_external_module(
	GIT_REPOSITORY https://github.com/cad420/VMUtils
	GIT_TAG        master
)

include_directories("{CMAKE_CURRENT_SOURCE_DIR}/src")

add_subdirectory(src)
