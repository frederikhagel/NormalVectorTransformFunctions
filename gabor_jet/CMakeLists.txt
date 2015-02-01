cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(gabor_jet)

find_package( OpenCV REQUIRED )

include_directories(include)

add_executable(gabor_jet
  main.cpp
  gaborJet.cpp
  gaborJet.hpp
  gaborWavelet.cpp
  gaborWavelet.hpp
)
target_link_libraries (gabor_jet ${OpenCV_LIBS} )

