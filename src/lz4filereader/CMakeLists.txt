cmake_minimum_required(VERSION 3.12)

project(lz4filereader)

find_package(lz4 CONFIG REQUIRED)
if(lz4_FOUND)

aux_source_directory(. SRC)

add_library(lz4filereader SHARED)
target_sources(lz4filereader PRIVATE ${SRC})
target_link_libraries(lz4filereader lz4::lz4)
target_include_directories(lz4filereader PRIVATE "interface" ${LZ4_INCLUDE_DIRS})
else()

endif()
