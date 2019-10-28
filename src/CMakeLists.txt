option(BUILD_VOXEL_EXTRACTOR "set on to build voxel extractor" ON)
if (BUILD_VOXEL_EXTRACTOR)
	add_subdirectory(voxel_extractor)
endif()

#option(BUILD_H264_VOXEL_READER "set on to build h264-voxel-reader" ON)
#if (BUILD_H264_VOXEL_READER)
#  add_subdirectory(h264_voxel_reader)
#endif()

#option(BUILD_LZ4_VOXEL_READER "set on to build lz4filereader" OFF)
#if(BUILD_LZ4_VOXEL_READER)
#add_subdirectory(lz4filereader)
#endif()
