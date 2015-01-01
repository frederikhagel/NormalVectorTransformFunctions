cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(compare_hist)

find_package( OpenCV REQUIRED )

add_executable (compare_hist compare_hist.cpp)
target_link_libraries (compare_hist ${OpenCV_LIBS} )

