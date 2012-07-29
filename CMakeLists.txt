cmake_minimum_required(VERSION 2.8)
project(rpcsvc)
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/output")
include_directories(${PROJECT_SOURCE_DIR}/include)
add_subdirectory(librpc)
add_subdirectory(rpcgen)
add_subdirectory(rpcinfo)

