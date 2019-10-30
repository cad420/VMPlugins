
set(VOCOMP_BUILD_VIDEO_COMPRESS OFF)
set(VOCOMP_BUILD_VIDEO_DECOMPRESS OFF)
set(VOCOMP_BUILD_REFINER OFF)
set(VOCOMP_BUILD_EXTRACTOR ON)

vm_external_module(
	GIT_REPOSITORY https://github.com/cad420/voxel-compression
	GIT_TAG        master
)
vm_external_module(
	GIT_REPOSITORY https://github.com/cad420/cuda-fx
	GIT_TAG        master
)
vm_external_module(
	GIT_REPOSITORY https://github.com/cad420/VMCore
	GIT_TAG        master
)

find_package(CUDA REQUIRED)
file(GLOB_RECURSE VOXEL_EXTRACTOR_SRC 
	**/*.cc
	*.cc
)
cuda_add_library(voxel_extractor SHARED
	${VOXEL_EXTRACTOR_SRC}
)
vm_target_dependency(voxel_extractor voxel_extract PRIVATE)
vm_target_dependency(voxel_extractor vmcore PUBLIC)
vm_target_dependency(voxel_extractor VMUtils PUBLIC)
vm_target_dependency(voxel_extractor cudafx PRIVATE)
target_link_libraries(voxel_extractor vmcore)

# option(BUILD_VOXEL_EXTRACTOR "set on to build voxel extractor" ON)
# if (BUILD_VOXEL_EXTRACTOR)
# 	add_subdirectory(voxel_extractor)
# endif()

#option(BUILD_H264_VOXEL_READER "set on to build h264-voxel-reader" ON)
#if (BUILD_H264_VOXEL_READER)
#  add_subdirectory(h264_voxel_reader)
#endif()

#option(BUILD_LZ4_VOXEL_READER "set on to build lz4filereader" OFF)
#if(BUILD_LZ4_VOXEL_READER)
#add_subdirectory(lz4filereader)
#endif()
