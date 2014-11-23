cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(billinear_interpolation)

find_package( OpenCV REQUIRED )

add_executable (billinear_interpolation cloud_viewer.cpp)
target_link_libraries (billinear_interpolation ${OpenCV_LIBS} )

