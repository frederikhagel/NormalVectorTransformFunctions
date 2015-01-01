cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(complete_transform_loop)

find_package(PCL 1.2 REQUIRED)
find_package( OpenCV REQUIRED )

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (complete_transform_loop transform_image.cpp)
target_link_libraries (complete_transform_loop ${PCL_LIBRARIES} ${OpenCV_LIBS} )

