option(BUILD_H264_VOXEL_READER "set on to build h264-voxel-reader" ON)

if (BUILD_H264_VOXEL_READER)
  add_subdirectory(h264_voxel_reader)
endif()
