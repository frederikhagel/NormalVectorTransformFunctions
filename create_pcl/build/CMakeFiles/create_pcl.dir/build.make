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
CMAKE_SOURCE_DIR = /home/frederik/pcl/create_pcl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/frederik/pcl/create_pcl/build

# Include any dependencies generated for this target.
include CMakeFiles/create_pcl.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/create_pcl.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/create_pcl.dir/flags.make

CMakeFiles/create_pcl.dir/create_pcl.cpp.o: CMakeFiles/create_pcl.dir/flags.make
CMakeFiles/create_pcl.dir/create_pcl.cpp.o: ../create_pcl.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/frederik/pcl/create_pcl/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/create_pcl.dir/create_pcl.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/create_pcl.dir/create_pcl.cpp.o -c /home/frederik/pcl/create_pcl/create_pcl.cpp

CMakeFiles/create_pcl.dir/create_pcl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/create_pcl.dir/create_pcl.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/frederik/pcl/create_pcl/create_pcl.cpp > CMakeFiles/create_pcl.dir/create_pcl.cpp.i

CMakeFiles/create_pcl.dir/create_pcl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/create_pcl.dir/create_pcl.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/frederik/pcl/create_pcl/create_pcl.cpp -o CMakeFiles/create_pcl.dir/create_pcl.cpp.s

CMakeFiles/create_pcl.dir/create_pcl.cpp.o.requires:
.PHONY : CMakeFiles/create_pcl.dir/create_pcl.cpp.o.requires

CMakeFiles/create_pcl.dir/create_pcl.cpp.o.provides: CMakeFiles/create_pcl.dir/create_pcl.cpp.o.requires
	$(MAKE) -f CMakeFiles/create_pcl.dir/build.make CMakeFiles/create_pcl.dir/create_pcl.cpp.o.provides.build
.PHONY : CMakeFiles/create_pcl.dir/create_pcl.cpp.o.provides

CMakeFiles/create_pcl.dir/create_pcl.cpp.o.provides.build: CMakeFiles/create_pcl.dir/create_pcl.cpp.o

# Object files for target create_pcl
create_pcl_OBJECTS = \
"CMakeFiles/create_pcl.dir/create_pcl.cpp.o"

# External object files for target create_pcl
create_pcl_EXTERNAL_OBJECTS =

create_pcl: CMakeFiles/create_pcl.dir/create_pcl.cpp.o
create_pcl: CMakeFiles/create_pcl.dir/build.make
create_pcl: /usr/lib/x86_64-linux-gnu/libboost_system.so
create_pcl: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
create_pcl: /usr/lib/x86_64-linux-gnu/libboost_thread.so
create_pcl: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
create_pcl: /usr/lib/x86_64-linux-gnu/libboost_iostreams.so
create_pcl: /usr/lib/x86_64-linux-gnu/libboost_serialization.so
create_pcl: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
create_pcl: /usr/lib/libpcl_common.so
create_pcl: /usr/lib/x86_64-linux-gnu/libflann_cpp_s.a
create_pcl: /usr/lib/libpcl_kdtree.so
create_pcl: /usr/lib/libpcl_octree.so
create_pcl: /usr/lib/libpcl_search.so
create_pcl: /usr/lib/x86_64-linux-gnu/libqhull.so
create_pcl: /usr/lib/libpcl_surface.so
create_pcl: /usr/lib/libpcl_sample_consensus.so
create_pcl: /usr/lib/libOpenNI.so
create_pcl: /usr/lib/libOpenNI2.so
create_pcl: /usr/lib/libvtkCommon.so.5.8.0
create_pcl: /usr/lib/libvtkFiltering.so.5.8.0
create_pcl: /usr/lib/libvtkImaging.so.5.8.0
create_pcl: /usr/lib/libvtkGraphics.so.5.8.0
create_pcl: /usr/lib/libvtkGenericFiltering.so.5.8.0
create_pcl: /usr/lib/libvtkIO.so.5.8.0
create_pcl: /usr/lib/libvtkRendering.so.5.8.0
create_pcl: /usr/lib/libvtkVolumeRendering.so.5.8.0
create_pcl: /usr/lib/libvtkHybrid.so.5.8.0
create_pcl: /usr/lib/libvtkWidgets.so.5.8.0
create_pcl: /usr/lib/libvtkParallel.so.5.8.0
create_pcl: /usr/lib/libvtkInfovis.so.5.8.0
create_pcl: /usr/lib/libvtkGeovis.so.5.8.0
create_pcl: /usr/lib/libvtkViews.so.5.8.0
create_pcl: /usr/lib/libvtkCharts.so.5.8.0
create_pcl: /usr/lib/libpcl_io.so
create_pcl: /usr/lib/libpcl_filters.so
create_pcl: /usr/lib/libpcl_features.so
create_pcl: /usr/lib/libpcl_keypoints.so
create_pcl: /usr/lib/libpcl_registration.so
create_pcl: /usr/lib/libpcl_segmentation.so
create_pcl: /usr/lib/libpcl_recognition.so
create_pcl: /usr/lib/libpcl_visualization.so
create_pcl: /usr/lib/libpcl_people.so
create_pcl: /usr/lib/libpcl_outofcore.so
create_pcl: /usr/lib/libpcl_tracking.so
create_pcl: /usr/lib/libpcl_apps.so
create_pcl: /usr/lib/x86_64-linux-gnu/libboost_system.so
create_pcl: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
create_pcl: /usr/lib/x86_64-linux-gnu/libboost_thread.so
create_pcl: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
create_pcl: /usr/lib/x86_64-linux-gnu/libboost_iostreams.so
create_pcl: /usr/lib/x86_64-linux-gnu/libboost_serialization.so
create_pcl: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
create_pcl: /usr/lib/x86_64-linux-gnu/libqhull.so
create_pcl: /usr/lib/libOpenNI.so
create_pcl: /usr/lib/libOpenNI2.so
create_pcl: /usr/lib/x86_64-linux-gnu/libflann_cpp_s.a
create_pcl: /usr/lib/libvtkCommon.so.5.8.0
create_pcl: /usr/lib/libvtkFiltering.so.5.8.0
create_pcl: /usr/lib/libvtkImaging.so.5.8.0
create_pcl: /usr/lib/libvtkGraphics.so.5.8.0
create_pcl: /usr/lib/libvtkGenericFiltering.so.5.8.0
create_pcl: /usr/lib/libvtkIO.so.5.8.0
create_pcl: /usr/lib/libvtkRendering.so.5.8.0
create_pcl: /usr/lib/libvtkVolumeRendering.so.5.8.0
create_pcl: /usr/lib/libvtkHybrid.so.5.8.0
create_pcl: /usr/lib/libvtkWidgets.so.5.8.0
create_pcl: /usr/lib/libvtkParallel.so.5.8.0
create_pcl: /usr/lib/libvtkInfovis.so.5.8.0
create_pcl: /usr/lib/libvtkGeovis.so.5.8.0
create_pcl: /usr/lib/libvtkViews.so.5.8.0
create_pcl: /usr/lib/libvtkCharts.so.5.8.0
create_pcl: /usr/local/lib/libopencv_xfeatures2d.so.3.0.0
create_pcl: /usr/local/lib/libopencv_tracking.so.3.0.0
create_pcl: /usr/local/lib/libopencv_text.so.3.0.0
create_pcl: /usr/local/lib/libopencv_surface_matching.so.3.0.0
create_pcl: /usr/local/lib/libopencv_reg.so.3.0.0
create_pcl: /usr/local/lib/libopencv_optflow.so.3.0.0
create_pcl: /usr/local/lib/libopencv_line_descriptor.so.3.0.0
create_pcl: /usr/local/lib/libopencv_latentsvm.so.3.0.0
create_pcl: /usr/local/lib/libopencv_ccalib.so.3.0.0
create_pcl: /usr/local/lib/libopencv_bioinspired.so.3.0.0
create_pcl: /usr/local/lib/libopencv_bgsegm.so.3.0.0
create_pcl: /usr/local/lib/libopencv_viz.so.3.0.0
create_pcl: /usr/local/lib/libopencv_videostab.so.3.0.0
create_pcl: /usr/local/lib/libopencv_videoio.so.3.0.0
create_pcl: /usr/local/lib/libopencv_video.so.3.0.0
create_pcl: /usr/local/lib/libopencv_ts.a
create_pcl: /usr/local/lib/libopencv_superres.so.3.0.0
create_pcl: /usr/local/lib/libopencv_stitching.so.3.0.0
create_pcl: /usr/local/lib/libopencv_shape.so.3.0.0
create_pcl: /usr/local/lib/libopencv_photo.so.3.0.0
create_pcl: /usr/local/lib/libopencv_objdetect.so.3.0.0
create_pcl: /usr/local/lib/libopencv_ml.so.3.0.0
create_pcl: /usr/local/lib/libopencv_imgproc.so.3.0.0
create_pcl: /usr/local/lib/libopencv_imgcodecs.so.3.0.0
create_pcl: /usr/local/lib/libopencv_highgui.so.3.0.0
create_pcl: /usr/local/lib/libopencv_flann.so.3.0.0
create_pcl: /usr/local/lib/libopencv_features2d.so.3.0.0
create_pcl: /usr/local/lib/libopencv_core.so.3.0.0
create_pcl: /usr/local/lib/libopencv_calib3d.so.3.0.0
create_pcl: /usr/lib/libpcl_common.so
create_pcl: /usr/lib/libpcl_kdtree.so
create_pcl: /usr/lib/libpcl_octree.so
create_pcl: /usr/lib/libpcl_search.so
create_pcl: /usr/lib/libpcl_surface.so
create_pcl: /usr/lib/libpcl_sample_consensus.so
create_pcl: /usr/lib/libpcl_io.so
create_pcl: /usr/lib/libpcl_filters.so
create_pcl: /usr/lib/libpcl_features.so
create_pcl: /usr/lib/libpcl_keypoints.so
create_pcl: /usr/lib/libpcl_registration.so
create_pcl: /usr/lib/libpcl_segmentation.so
create_pcl: /usr/lib/libpcl_recognition.so
create_pcl: /usr/lib/libpcl_visualization.so
create_pcl: /usr/lib/libpcl_people.so
create_pcl: /usr/lib/libpcl_outofcore.so
create_pcl: /usr/lib/libpcl_tracking.so
create_pcl: /usr/lib/libpcl_apps.so
create_pcl: /usr/lib/libvtkGenericFiltering.so.5.8.0
create_pcl: /usr/lib/libvtkGeovis.so.5.8.0
create_pcl: /usr/lib/libvtkCharts.so.5.8.0
create_pcl: /usr/lib/libvtkViews.so.5.8.0
create_pcl: /usr/lib/libvtkInfovis.so.5.8.0
create_pcl: /usr/lib/libvtkWidgets.so.5.8.0
create_pcl: /usr/lib/libvtkVolumeRendering.so.5.8.0
create_pcl: /usr/lib/libvtkHybrid.so.5.8.0
create_pcl: /usr/lib/libvtkParallel.so.5.8.0
create_pcl: /usr/lib/libvtkRendering.so.5.8.0
create_pcl: /usr/lib/libvtkImaging.so.5.8.0
create_pcl: /usr/lib/libvtkGraphics.so.5.8.0
create_pcl: /usr/lib/libvtkIO.so.5.8.0
create_pcl: /usr/lib/libvtkFiltering.so.5.8.0
create_pcl: /usr/lib/libvtkCommon.so.5.8.0
create_pcl: /usr/lib/libvtksys.so.5.8.0
create_pcl: /usr/local/share/OpenCV/3rdparty/lib/libippicv.a
create_pcl: /usr/local/lib/libopencv_xfeatures2d.so.3.0.0
create_pcl: /usr/local/lib/libopencv_shape.so.3.0.0
create_pcl: /usr/local/lib/libopencv_video.so.3.0.0
create_pcl: /usr/local/lib/libopencv_calib3d.so.3.0.0
create_pcl: /usr/local/lib/libopencv_features2d.so.3.0.0
create_pcl: /usr/local/lib/libopencv_ml.so.3.0.0
create_pcl: /usr/local/lib/libopencv_highgui.so.3.0.0
create_pcl: /usr/local/lib/libopencv_videoio.so.3.0.0
create_pcl: /usr/local/lib/libopencv_imgcodecs.so.3.0.0
create_pcl: /usr/local/lib/libopencv_imgproc.so.3.0.0
create_pcl: /usr/local/lib/libopencv_flann.so.3.0.0
create_pcl: /usr/local/lib/libopencv_core.so.3.0.0
create_pcl: CMakeFiles/create_pcl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable create_pcl"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/create_pcl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/create_pcl.dir/build: create_pcl
.PHONY : CMakeFiles/create_pcl.dir/build

CMakeFiles/create_pcl.dir/requires: CMakeFiles/create_pcl.dir/create_pcl.cpp.o.requires
.PHONY : CMakeFiles/create_pcl.dir/requires

CMakeFiles/create_pcl.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/create_pcl.dir/cmake_clean.cmake
.PHONY : CMakeFiles/create_pcl.dir/clean

CMakeFiles/create_pcl.dir/depend:
	cd /home/frederik/pcl/create_pcl/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/frederik/pcl/create_pcl /home/frederik/pcl/create_pcl /home/frederik/pcl/create_pcl/build /home/frederik/pcl/create_pcl/build /home/frederik/pcl/create_pcl/build/CMakeFiles/create_pcl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/create_pcl.dir/depend

