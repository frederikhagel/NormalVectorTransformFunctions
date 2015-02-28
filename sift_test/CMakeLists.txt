cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(sift_test)

include_directories(-I/usr/include/opencv2)
find_package( OpenCV REQUIRED )

add_executable (sift_test sift_test.cpp)
target_link_libraries (sift_test ${OpenCV_LIBS} )

