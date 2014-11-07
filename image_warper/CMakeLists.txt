cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(image_warper)

find_package( OpenCV REQUIRED )

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_DEFINITIONS})

add_executable (image_warper code.cpp)
target_link_libraries (image_warper ${OpenCV_LIBRARIES})
