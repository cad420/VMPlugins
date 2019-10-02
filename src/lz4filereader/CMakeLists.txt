cmake_minimum_required(VERSION 3.12)

project(lz4filereader)

find_package(lz4 CONFIG REQUIRED)
if(lz4_FOUND)
message(STATUS "LZ4 Found")
aux_source_directory(. SRC)

add_library(lz4filereader SHARED)
target_sources(lz4filereader PRIVATE ${SRC})

vm_target_dependency(lz4filereader vmcore PRIVATE)
target_link_libraries(lz4filereader lz4::lz4)
target_include_directories(lz4filereader PRIVATE ${lz4_INCLUDE_DIRS})
install(TARGETS lz4filereader LIBRARY DESTINATION "lib" RUNTIME DESTINATION "bin" ARCHIVE DESTINATION "lib")
elseif()
message(FATAL_ERROR "LZ4 NOT FOUND")
endif()
