cmake_minimum_required(VERSION 3.12)

project(h264_voxel_reader)

aux_source_directory(. SRC)
add_library(h264_voxel_reader SHARED)
target_sources(h264_voxel_reader PRIVATE ${SRC})
target_link_libraries(h264_voxel_reader vmcore)
install(TARGETS h264_voxel_reader LIBRARY DESTINATION "lib" RUNTIME DESTINATION "bin" ARCHIVE DESTINATION "lib")

