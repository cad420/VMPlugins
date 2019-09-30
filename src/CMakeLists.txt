option(BUILD_H264_VOXEL_READER "set on to build h264-voxel-reader" ON)

if (BUILD_H264_VOXEL_READER)
  add_subdirectory(h264_voxel_reader)
endif()

option(BUILD_LZ4_VOXEL_READER "set on to build lz4filereader" ON)
if(BUILD_LZ4_VOXEL_READER)
add_subdirectory(lz4filereader)
endif()
