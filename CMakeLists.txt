cmake_minimum_required(VERSION 2.8)

project(rpcsvc)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/output")
include_directories(${PROJECT_SOURCE_DIR}/include)
add_subdirectory(librpc)
add_subdirectory(rpcgen)
add_subdirectory(rpcinfo)
add_subdirectory(mountd)
add_subdirectory(nfsd)

