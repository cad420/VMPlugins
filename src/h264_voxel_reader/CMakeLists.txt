file(GLOB_RECURSE H264_SOURCES "*.cc")

add_library(h264_voxel_reader SHARED ${H264_SOURCES} ${COMMON_SOURCES})
