cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(transform_perspective_transform)

find_package(PCL 1.2 REQUIRED)
find_package( OpenCV REQUIRED )

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (transform_perspective_transform transform_perspective_transform.cpp)
target_link_libraries (transform_perspective_transform ${PCL_LIBRARIES} ${OpenCV_LIBS} )

