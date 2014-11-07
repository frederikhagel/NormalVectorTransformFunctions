cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(normal_viewer)

find_package(PCL 1.2 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (normal_viewer normal_viewer.cpp)
target_link_libraries (normal_viewer ${PCL_LIBRARIES})

