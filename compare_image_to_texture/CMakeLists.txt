cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(compare_image_to_texture)

find_package( OpenCV REQUIRED )

add_executable (compare_image_to_texture compare_image.cpp)
target_link_libraries (compare_image_to_texture ${OpenCV_LIBS} )

