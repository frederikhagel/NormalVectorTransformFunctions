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
CMAKE_SOURCE_DIR = /home/frederik/pcl/compare_image_to_texture

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/frederik/pcl/compare_image_to_texture

# Include any dependencies generated for this target.
include CMakeFiles/compare_image_to_texture.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/compare_image_to_texture.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/compare_image_to_texture.dir/flags.make

CMakeFiles/compare_image_to_texture.dir/compare_image.cpp.o: CMakeFiles/compare_image_to_texture.dir/flags.make
CMakeFiles/compare_image_to_texture.dir/compare_image.cpp.o: compare_image.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/frederik/pcl/compare_image_to_texture/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/compare_image_to_texture.dir/compare_image.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/compare_image_to_texture.dir/compare_image.cpp.o -c /home/frederik/pcl/compare_image_to_texture/compare_image.cpp

CMakeFiles/compare_image_to_texture.dir/compare_image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compare_image_to_texture.dir/compare_image.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/frederik/pcl/compare_image_to_texture/compare_image.cpp > CMakeFiles/compare_image_to_texture.dir/compare_image.cpp.i

CMakeFiles/compare_image_to_texture.dir/compare_image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compare_image_to_texture.dir/compare_image.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/frederik/pcl/compare_image_to_texture/compare_image.cpp -o CMakeFiles/compare_image_to_texture.dir/compare_image.cpp.s

CMakeFiles/compare_image_to_texture.dir/compare_image.cpp.o.requires:
.PHONY : CMakeFiles/compare_image_to_texture.dir/compare_image.cpp.o.requires

CMakeFiles/compare_image_to_texture.dir/compare_image.cpp.o.provides: CMakeFiles/compare_image_to_texture.dir/compare_image.cpp.o.requires
	$(MAKE) -f CMakeFiles/compare_image_to_texture.dir/build.make CMakeFiles/compare_image_to_texture.dir/compare_image.cpp.o.provides.build
.PHONY : CMakeFiles/compare_image_to_texture.dir/compare_image.cpp.o.provides

CMakeFiles/compare_image_to_texture.dir/compare_image.cpp.o.provides.build: CMakeFiles/compare_image_to_texture.dir/compare_image.cpp.o

# Object files for target compare_image_to_texture
compare_image_to_texture_OBJECTS = \
"CMakeFiles/compare_image_to_texture.dir/compare_image.cpp.o"

# External object files for target compare_image_to_texture
compare_image_to_texture_EXTERNAL_OBJECTS =

compare_image_to_texture: CMakeFiles/compare_image_to_texture.dir/compare_image.cpp.o
compare_image_to_texture: CMakeFiles/compare_image_to_texture.dir/build.make
compare_image_to_texture: /usr/local/lib/libopencv_viz.so.3.0.0
compare_image_to_texture: /usr/local/lib/libopencv_videostab.so.3.0.0
compare_image_to_texture: /usr/local/lib/libopencv_videoio.so.3.0.0
compare_image_to_texture: /usr/local/lib/libopencv_video.so.3.0.0
compare_image_to_texture: /usr/local/lib/libopencv_ts.a
compare_image_to_texture: /usr/local/lib/libopencv_superres.so.3.0.0
compare_image_to_texture: /usr/local/lib/libopencv_stitching.so.3.0.0
compare_image_to_texture: /usr/local/lib/libopencv_shape.so.3.0.0
compare_image_to_texture: /usr/local/lib/libopencv_photo.so.3.0.0
compare_image_to_texture: /usr/local/lib/libopencv_objdetect.so.3.0.0
compare_image_to_texture: /usr/local/lib/libopencv_ml.so.3.0.0
compare_image_to_texture: /usr/local/lib/libopencv_imgproc.so.3.0.0
compare_image_to_texture: /usr/local/lib/libopencv_imgcodecs.so.3.0.0
compare_image_to_texture: /usr/local/lib/libopencv_highgui.so.3.0.0
compare_image_to_texture: /usr/local/lib/libopencv_flann.so.3.0.0
compare_image_to_texture: /usr/local/lib/libopencv_features2d.so.3.0.0
compare_image_to_texture: /usr/local/lib/libopencv_core.so.3.0.0
compare_image_to_texture: /usr/local/lib/libopencv_calib3d.so.3.0.0
compare_image_to_texture: /usr/local/share/OpenCV/3rdparty/lib/libippicv.a
compare_image_to_texture: /usr/local/lib/libopencv_features2d.so.3.0.0
compare_image_to_texture: /usr/local/lib/libopencv_ml.so.3.0.0
compare_image_to_texture: /usr/local/lib/libopencv_highgui.so.3.0.0
compare_image_to_texture: /usr/local/lib/libopencv_videoio.so.3.0.0
compare_image_to_texture: /usr/local/lib/libopencv_imgcodecs.so.3.0.0
compare_image_to_texture: /usr/local/lib/libopencv_flann.so.3.0.0
compare_image_to_texture: /usr/local/lib/libopencv_video.so.3.0.0
compare_image_to_texture: /usr/local/lib/libopencv_imgproc.so.3.0.0
compare_image_to_texture: /usr/local/lib/libopencv_core.so.3.0.0
compare_image_to_texture: CMakeFiles/compare_image_to_texture.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable compare_image_to_texture"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/compare_image_to_texture.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/compare_image_to_texture.dir/build: compare_image_to_texture
.PHONY : CMakeFiles/compare_image_to_texture.dir/build

CMakeFiles/compare_image_to_texture.dir/requires: CMakeFiles/compare_image_to_texture.dir/compare_image.cpp.o.requires
.PHONY : CMakeFiles/compare_image_to_texture.dir/requires

CMakeFiles/compare_image_to_texture.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/compare_image_to_texture.dir/cmake_clean.cmake
.PHONY : CMakeFiles/compare_image_to_texture.dir/clean

CMakeFiles/compare_image_to_texture.dir/depend:
	cd /home/frederik/pcl/compare_image_to_texture && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/frederik/pcl/compare_image_to_texture /home/frederik/pcl/compare_image_to_texture /home/frederik/pcl/compare_image_to_texture /home/frederik/pcl/compare_image_to_texture /home/frederik/pcl/compare_image_to_texture/CMakeFiles/compare_image_to_texture.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/compare_image_to_texture.dir/depend
