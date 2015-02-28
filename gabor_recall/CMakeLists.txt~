cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(daft_image_test)

find_package(COVIS HINTS ~/covis/build)
add_definitions(${COVIS_DEFINITIONS})
include_directories(${COVIS_INCLUDE_DIRS})

find_package(PCL 1.2 REQUIRED )
find_package( OpenCV REQUIRED )

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(compare_daft
  main.cpp
  gaborMatcher.cpp
  gaborMatcher.hpp
  transform.hpp
  transform.cpp
)


target_link_libraries ( compare_daft ${COVIS_LIBRARIES} ${PCL_LIBRARIES} ${OpenCV_LIBS} )

