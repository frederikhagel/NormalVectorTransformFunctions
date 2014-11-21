cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(transform_and_project)

find_package(PCL 1.2 REQUIRED)
find_package( OpenCV REQUIRED )

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (transform_and_project cloud_viewer.cpp)
target_link_libraries (transform_and_project ${PCL_LIBRARIES} ${OpenCV_LIBS} )

