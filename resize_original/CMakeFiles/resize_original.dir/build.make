# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/frederik/pcl/resize_original

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/frederik/pcl/resize_original

# Include any dependencies generated for this target.
include CMakeFiles/resize_original.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/resize_original.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/resize_original.dir/flags.make

CMakeFiles/resize_original.dir/resize_original.cpp.o: CMakeFiles/resize_original.dir/flags.make
CMakeFiles/resize_original.dir/resize_original.cpp.o: resize_original.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/frederik/pcl/resize_original/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/resize_original.dir/resize_original.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/resize_original.dir/resize_original.cpp.o -c /home/frederik/pcl/resize_original/resize_original.cpp

CMakeFiles/resize_original.dir/resize_original.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/resize_original.dir/resize_original.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/frederik/pcl/resize_original/resize_original.cpp > CMakeFiles/resize_original.dir/resize_original.cpp.i

CMakeFiles/resize_original.dir/resize_original.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/resize_original.dir/resize_original.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/frederik/pcl/resize_original/resize_original.cpp -o CMakeFiles/resize_original.dir/resize_original.cpp.s

CMakeFiles/resize_original.dir/resize_original.cpp.o.requires:
.PHONY : CMakeFiles/resize_original.dir/resize_original.cpp.o.requires

CMakeFiles/resize_original.dir/resize_original.cpp.o.provides: CMakeFiles/resize_original.dir/resize_original.cpp.o.requires
	$(MAKE) -f CMakeFiles/resize_original.dir/build.make CMakeFiles/resize_original.dir/resize_original.cpp.o.provides.build
.PHONY : CMakeFiles/resize_original.dir/resize_original.cpp.o.provides

CMakeFiles/resize_original.dir/resize_original.cpp.o.provides.build: CMakeFiles/resize_original.dir/resize_original.cpp.o

# Object files for target resize_original
resize_original_OBJECTS = \
"CMakeFiles/resize_original.dir/resize_original.cpp.o"

# External object files for target resize_original
resize_original_EXTERNAL_OBJECTS =

resize_original: CMakeFiles/resize_original.dir/resize_original.cpp.o
resize_original: CMakeFiles/resize_original.dir/build.make
resize_original: /usr/local/lib/libopencv_viz.so.3.0.0
resize_original: /usr/local/lib/libopencv_videostab.so.3.0.0
resize_original: /usr/local/lib/libopencv_videoio.so.3.0.0
resize_original: /usr/local/lib/libopencv_video.so.3.0.0
resize_original: /usr/local/lib/libopencv_ts.a
resize_original: /usr/local/lib/libopencv_superres.so.3.0.0
resize_original: /usr/local/lib/libopencv_stitching.so.3.0.0
resize_original: /usr/local/lib/libopencv_shape.so.3.0.0
resize_original: /usr/local/lib/libopencv_photo.so.3.0.0
resize_original: /usr/local/lib/libopencv_objdetect.so.3.0.0
resize_original: /usr/local/lib/libopencv_ml.so.3.0.0
resize_original: /usr/local/lib/libopencv_imgproc.so.3.0.0
resize_original: /usr/local/lib/libopencv_imgcodecs.so.3.0.0
resize_original: /usr/local/lib/libopencv_highgui.so.3.0.0
resize_original: /usr/local/lib/libopencv_flann.so.3.0.0
resize_original: /usr/local/lib/libopencv_features2d.so.3.0.0
resize_original: /usr/local/lib/libopencv_core.so.3.0.0
resize_original: /usr/local/lib/libopencv_calib3d.so.3.0.0
resize_original: /usr/local/share/OpenCV/3rdparty/lib/libippicv.a
resize_original: /usr/local/lib/libopencv_features2d.so.3.0.0
resize_original: /usr/local/lib/libopencv_ml.so.3.0.0
resize_original: /usr/local/lib/libopencv_highgui.so.3.0.0
resize_original: /usr/local/lib/libopencv_videoio.so.3.0.0
resize_original: /usr/local/lib/libopencv_imgcodecs.so.3.0.0
resize_original: /usr/local/lib/libopencv_flann.so.3.0.0
resize_original: /usr/local/lib/libopencv_video.so.3.0.0
resize_original: /usr/local/lib/libopencv_imgproc.so.3.0.0
resize_original: /usr/local/lib/libopencv_core.so.3.0.0
resize_original: CMakeFiles/resize_original.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable resize_original"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/resize_original.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/resize_original.dir/build: resize_original
.PHONY : CMakeFiles/resize_original.dir/build

CMakeFiles/resize_original.dir/requires: CMakeFiles/resize_original.dir/resize_original.cpp.o.requires
.PHONY : CMakeFiles/resize_original.dir/requires

CMakeFiles/resize_original.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/resize_original.dir/cmake_clean.cmake
.PHONY : CMakeFiles/resize_original.dir/clean

CMakeFiles/resize_original.dir/depend:
	cd /home/frederik/pcl/resize_original && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/frederik/pcl/resize_original /home/frederik/pcl/resize_original /home/frederik/pcl/resize_original /home/frederik/pcl/resize_original /home/frederik/pcl/resize_original/CMakeFiles/resize_original.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/resize_original.dir/depend

