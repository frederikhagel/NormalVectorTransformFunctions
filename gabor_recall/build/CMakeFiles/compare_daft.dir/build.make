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
CMAKE_SOURCE_DIR = /home/frederik/pcl/gabor_recall

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/frederik/pcl/gabor_recall/build

# Include any dependencies generated for this target.
include CMakeFiles/compare_daft.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/compare_daft.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/compare_daft.dir/flags.make

CMakeFiles/compare_daft.dir/main.cpp.o: CMakeFiles/compare_daft.dir/flags.make
CMakeFiles/compare_daft.dir/main.cpp.o: ../main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/frederik/pcl/gabor_recall/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/compare_daft.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/compare_daft.dir/main.cpp.o -c /home/frederik/pcl/gabor_recall/main.cpp

CMakeFiles/compare_daft.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compare_daft.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/frederik/pcl/gabor_recall/main.cpp > CMakeFiles/compare_daft.dir/main.cpp.i

CMakeFiles/compare_daft.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compare_daft.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/frederik/pcl/gabor_recall/main.cpp -o CMakeFiles/compare_daft.dir/main.cpp.s

CMakeFiles/compare_daft.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/compare_daft.dir/main.cpp.o.requires

CMakeFiles/compare_daft.dir/main.cpp.o.provides: CMakeFiles/compare_daft.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/compare_daft.dir/build.make CMakeFiles/compare_daft.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/compare_daft.dir/main.cpp.o.provides

CMakeFiles/compare_daft.dir/main.cpp.o.provides.build: CMakeFiles/compare_daft.dir/main.cpp.o

CMakeFiles/compare_daft.dir/transform.cpp.o: CMakeFiles/compare_daft.dir/flags.make
CMakeFiles/compare_daft.dir/transform.cpp.o: ../transform.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/frederik/pcl/gabor_recall/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/compare_daft.dir/transform.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/compare_daft.dir/transform.cpp.o -c /home/frederik/pcl/gabor_recall/transform.cpp

CMakeFiles/compare_daft.dir/transform.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compare_daft.dir/transform.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/frederik/pcl/gabor_recall/transform.cpp > CMakeFiles/compare_daft.dir/transform.cpp.i

CMakeFiles/compare_daft.dir/transform.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compare_daft.dir/transform.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/frederik/pcl/gabor_recall/transform.cpp -o CMakeFiles/compare_daft.dir/transform.cpp.s

CMakeFiles/compare_daft.dir/transform.cpp.o.requires:
.PHONY : CMakeFiles/compare_daft.dir/transform.cpp.o.requires

CMakeFiles/compare_daft.dir/transform.cpp.o.provides: CMakeFiles/compare_daft.dir/transform.cpp.o.requires
	$(MAKE) -f CMakeFiles/compare_daft.dir/build.make CMakeFiles/compare_daft.dir/transform.cpp.o.provides.build
.PHONY : CMakeFiles/compare_daft.dir/transform.cpp.o.provides

CMakeFiles/compare_daft.dir/transform.cpp.o.provides.build: CMakeFiles/compare_daft.dir/transform.cpp.o

# Object files for target compare_daft
compare_daft_OBJECTS = \
"CMakeFiles/compare_daft.dir/main.cpp.o" \
"CMakeFiles/compare_daft.dir/transform.cpp.o"

# External object files for target compare_daft
compare_daft_EXTERNAL_OBJECTS =

compare_daft: CMakeFiles/compare_daft.dir/main.cpp.o
compare_daft: CMakeFiles/compare_daft.dir/transform.cpp.o
compare_daft: CMakeFiles/compare_daft.dir/build.make
compare_daft: /usr/local/lib/libopencv_viz.so.3.0.0
compare_daft: /usr/local/lib/libopencv_videostab.so.3.0.0
compare_daft: /usr/local/lib/libopencv_videoio.so.3.0.0
compare_daft: /usr/local/lib/libopencv_video.so.3.0.0
compare_daft: /usr/local/lib/libopencv_ts.a
compare_daft: /usr/local/lib/libopencv_superres.so.3.0.0
compare_daft: /usr/local/lib/libopencv_stitching.so.3.0.0
compare_daft: /usr/local/lib/libopencv_shape.so.3.0.0
compare_daft: /usr/local/lib/libopencv_photo.so.3.0.0
compare_daft: /usr/local/lib/libopencv_objdetect.so.3.0.0
compare_daft: /usr/local/lib/libopencv_ml.so.3.0.0
compare_daft: /usr/local/lib/libopencv_imgproc.so.3.0.0
compare_daft: /usr/local/lib/libopencv_imgcodecs.so.3.0.0
compare_daft: /usr/local/lib/libopencv_highgui.so.3.0.0
compare_daft: /usr/local/lib/libopencv_flann.so.3.0.0
compare_daft: /usr/local/lib/libopencv_features2d.so.3.0.0
compare_daft: /usr/local/lib/libopencv_core.so.3.0.0
compare_daft: /usr/local/lib/libopencv_calib3d.so.3.0.0
compare_daft: /usr/lib/x86_64-linux-gnu/libboost_program_options.so
compare_daft: /usr/lib/x86_64-linux-gnu/libboost_unit_test_framework.so
compare_daft: /usr/lib/x86_64-linux-gnu/libboost_test_exec_monitor.a
compare_daft: /usr/lib/x86_64-linux-gnu/libboost_system.so
compare_daft: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
compare_daft: /usr/lib/x86_64-linux-gnu/libboost_thread.so
compare_daft: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
compare_daft: /usr/lib/x86_64-linux-gnu/libboost_iostreams.so
compare_daft: /usr/lib/x86_64-linux-gnu/libboost_serialization.so
compare_daft: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
compare_daft: /usr/lib/libpcl_common.so
compare_daft: /usr/lib/x86_64-linux-gnu/libflann_cpp_s.a
compare_daft: /usr/lib/libpcl_kdtree.so
compare_daft: /usr/lib/libpcl_octree.so
compare_daft: /usr/lib/libpcl_search.so
compare_daft: /usr/lib/x86_64-linux-gnu/libqhull.so
compare_daft: /usr/lib/libpcl_surface.so
compare_daft: /usr/lib/libpcl_sample_consensus.so
compare_daft: /usr/lib/libOpenNI.so
compare_daft: /usr/lib/libOpenNI2.so
compare_daft: /usr/lib/libvtkCommon.so.5.8.0
compare_daft: /usr/lib/libvtkFiltering.so.5.8.0
compare_daft: /usr/lib/libvtkImaging.so.5.8.0
compare_daft: /usr/lib/libvtkGraphics.so.5.8.0
compare_daft: /usr/lib/libvtkGenericFiltering.so.5.8.0
compare_daft: /usr/lib/libvtkIO.so.5.8.0
compare_daft: /usr/lib/libvtkRendering.so.5.8.0
compare_daft: /usr/lib/libvtkVolumeRendering.so.5.8.0
compare_daft: /usr/lib/libvtkHybrid.so.5.8.0
compare_daft: /usr/lib/libvtkWidgets.so.5.8.0
compare_daft: /usr/lib/libvtkParallel.so.5.8.0
compare_daft: /usr/lib/libvtkInfovis.so.5.8.0
compare_daft: /usr/lib/libvtkGeovis.so.5.8.0
compare_daft: /usr/lib/libvtkViews.so.5.8.0
compare_daft: /usr/lib/libvtkCharts.so.5.8.0
compare_daft: /usr/lib/libpcl_io.so
compare_daft: /usr/lib/libpcl_filters.so
compare_daft: /usr/lib/libpcl_features.so
compare_daft: /usr/lib/libpcl_keypoints.so
compare_daft: /usr/lib/libpcl_registration.so
compare_daft: /usr/lib/libpcl_segmentation.so
compare_daft: /usr/lib/libpcl_recognition.so
compare_daft: /usr/lib/libpcl_visualization.so
compare_daft: /usr/lib/libpcl_people.so
compare_daft: /usr/lib/libpcl_outofcore.so
compare_daft: /usr/lib/libpcl_tracking.so
compare_daft: /usr/lib/libpcl_apps.so
compare_daft: /home/frederik/covis/build/lib/libcovis.so
compare_daft: /usr/lib/x86_64-linux-gnu/libboost_system.so
compare_daft: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
compare_daft: /usr/lib/x86_64-linux-gnu/libboost_thread.so
compare_daft: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
compare_daft: /usr/lib/x86_64-linux-gnu/libboost_iostreams.so
compare_daft: /usr/lib/x86_64-linux-gnu/libboost_serialization.so
compare_daft: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
compare_daft: /usr/lib/libpcl_common.so
compare_daft: /usr/lib/x86_64-linux-gnu/libflann_cpp_s.a
compare_daft: /usr/lib/libpcl_kdtree.so
compare_daft: /usr/lib/libpcl_octree.so
compare_daft: /usr/lib/libpcl_search.so
compare_daft: /usr/lib/x86_64-linux-gnu/libqhull.so
compare_daft: /usr/lib/libpcl_surface.so
compare_daft: /usr/lib/libpcl_sample_consensus.so
compare_daft: /usr/lib/libOpenNI.so
compare_daft: /usr/lib/libOpenNI2.so
compare_daft: /usr/lib/libvtkCommon.so.5.8.0
compare_daft: /usr/lib/libvtkFiltering.so.5.8.0
compare_daft: /usr/lib/libvtkImaging.so.5.8.0
compare_daft: /usr/lib/libvtkGraphics.so.5.8.0
compare_daft: /usr/lib/libvtkGenericFiltering.so.5.8.0
compare_daft: /usr/lib/libvtkIO.so.5.8.0
compare_daft: /usr/lib/libvtkRendering.so.5.8.0
compare_daft: /usr/lib/libvtkVolumeRendering.so.5.8.0
compare_daft: /usr/lib/libvtkHybrid.so.5.8.0
compare_daft: /usr/lib/libvtkWidgets.so.5.8.0
compare_daft: /usr/lib/libvtkParallel.so.5.8.0
compare_daft: /usr/lib/libvtkInfovis.so.5.8.0
compare_daft: /usr/lib/libvtkGeovis.so.5.8.0
compare_daft: /usr/lib/libvtkViews.so.5.8.0
compare_daft: /usr/lib/libvtkCharts.so.5.8.0
compare_daft: /usr/lib/libpcl_io.so
compare_daft: /usr/lib/libpcl_filters.so
compare_daft: /usr/lib/libpcl_features.so
compare_daft: /usr/lib/libpcl_keypoints.so
compare_daft: /usr/lib/libpcl_registration.so
compare_daft: /usr/lib/libpcl_segmentation.so
compare_daft: /usr/lib/libpcl_recognition.so
compare_daft: /usr/lib/libpcl_visualization.so
compare_daft: /usr/lib/libpcl_people.so
compare_daft: /usr/lib/libpcl_outofcore.so
compare_daft: /usr/lib/libpcl_tracking.so
compare_daft: /usr/lib/libpcl_apps.so
compare_daft: /usr/lib/x86_64-linux-gnu/libboost_system.so
compare_daft: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
compare_daft: /usr/lib/x86_64-linux-gnu/libboost_thread.so
compare_daft: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
compare_daft: /usr/lib/x86_64-linux-gnu/libboost_iostreams.so
compare_daft: /usr/lib/x86_64-linux-gnu/libboost_serialization.so
compare_daft: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
compare_daft: /usr/lib/x86_64-linux-gnu/libqhull.so
compare_daft: /usr/lib/libOpenNI.so
compare_daft: /usr/lib/libOpenNI2.so
compare_daft: /usr/lib/x86_64-linux-gnu/libflann_cpp_s.a
compare_daft: /usr/lib/libvtkCommon.so.5.8.0
compare_daft: /usr/lib/libvtkFiltering.so.5.8.0
compare_daft: /usr/lib/libvtkImaging.so.5.8.0
compare_daft: /usr/lib/libvtkGraphics.so.5.8.0
compare_daft: /usr/lib/libvtkGenericFiltering.so.5.8.0
compare_daft: /usr/lib/libvtkIO.so.5.8.0
compare_daft: /usr/lib/libvtkRendering.so.5.8.0
compare_daft: /usr/lib/libvtkVolumeRendering.so.5.8.0
compare_daft: /usr/lib/libvtkHybrid.so.5.8.0
compare_daft: /usr/lib/libvtkWidgets.so.5.8.0
compare_daft: /usr/lib/libvtkParallel.so.5.8.0
compare_daft: /usr/lib/libvtkInfovis.so.5.8.0
compare_daft: /usr/lib/libvtkGeovis.so.5.8.0
compare_daft: /usr/lib/libvtkViews.so.5.8.0
compare_daft: /usr/lib/libvtkCharts.so.5.8.0
compare_daft: /usr/local/lib/libopencv_xfeatures2d.so.3.0.0
compare_daft: /usr/local/lib/libopencv_tracking.so.3.0.0
compare_daft: /usr/local/lib/libopencv_text.so.3.0.0
compare_daft: /usr/local/lib/libopencv_surface_matching.so.3.0.0
compare_daft: /usr/local/lib/libopencv_reg.so.3.0.0
compare_daft: /usr/local/lib/libopencv_optflow.so.3.0.0
compare_daft: /usr/local/lib/libopencv_line_descriptor.so.3.0.0
compare_daft: /usr/local/lib/libopencv_latentsvm.so.3.0.0
compare_daft: /usr/local/lib/libopencv_ccalib.so.3.0.0
compare_daft: /usr/local/lib/libopencv_bioinspired.so.3.0.0
compare_daft: /usr/local/lib/libopencv_bgsegm.so.3.0.0
compare_daft: /usr/local/lib/libopencv_viz.so.3.0.0
compare_daft: /usr/local/lib/libopencv_videostab.so.3.0.0
compare_daft: /usr/local/lib/libopencv_videoio.so.3.0.0
compare_daft: /usr/local/lib/libopencv_video.so.3.0.0
compare_daft: /usr/local/lib/libopencv_ts.a
compare_daft: /usr/local/lib/libopencv_superres.so.3.0.0
compare_daft: /usr/local/lib/libopencv_stitching.so.3.0.0
compare_daft: /usr/local/lib/libopencv_shape.so.3.0.0
compare_daft: /usr/local/lib/libopencv_photo.so.3.0.0
compare_daft: /usr/local/lib/libopencv_objdetect.so.3.0.0
compare_daft: /usr/local/lib/libopencv_ml.so.3.0.0
compare_daft: /usr/local/lib/libopencv_imgproc.so.3.0.0
compare_daft: /usr/local/lib/libopencv_imgcodecs.so.3.0.0
compare_daft: /usr/local/lib/libopencv_highgui.so.3.0.0
compare_daft: /usr/local/lib/libopencv_flann.so.3.0.0
compare_daft: /usr/local/lib/libopencv_features2d.so.3.0.0
compare_daft: /usr/local/lib/libopencv_core.so.3.0.0
compare_daft: /usr/local/lib/libopencv_calib3d.so.3.0.0
compare_daft: /usr/lib/libvtkGenericFiltering.so.5.8.0
compare_daft: /usr/lib/libvtkGeovis.so.5.8.0
compare_daft: /usr/lib/libvtkCharts.so.5.8.0
compare_daft: /usr/lib/libvtkViews.so.5.8.0
compare_daft: /usr/lib/libvtkInfovis.so.5.8.0
compare_daft: /usr/lib/libvtkWidgets.so.5.8.0
compare_daft: /usr/lib/libvtkVolumeRendering.so.5.8.0
compare_daft: /usr/lib/libvtkHybrid.so.5.8.0
compare_daft: /usr/lib/libvtkParallel.so.5.8.0
compare_daft: /usr/lib/libvtkRendering.so.5.8.0
compare_daft: /usr/lib/libvtkImaging.so.5.8.0
compare_daft: /usr/lib/libvtkGraphics.so.5.8.0
compare_daft: /usr/lib/libvtkIO.so.5.8.0
compare_daft: /usr/lib/libvtkFiltering.so.5.8.0
compare_daft: /usr/lib/libvtkCommon.so.5.8.0
compare_daft: /usr/lib/libvtksys.so.5.8.0
compare_daft: /usr/local/share/OpenCV/3rdparty/lib/libippicv.a
compare_daft: /usr/local/lib/libopencv_xfeatures2d.so.3.0.0
compare_daft: /usr/local/lib/libopencv_shape.so.3.0.0
compare_daft: /home/frederik/covis/build/lib/libcovis.so
compare_daft: /usr/local/lib/libopencv_calib3d.so.3.0.0
compare_daft: /usr/local/lib/libopencv_features2d.so.3.0.0
compare_daft: /usr/local/lib/libopencv_ml.so.3.0.0
compare_daft: /usr/local/lib/libopencv_flann.so.3.0.0
compare_daft: /usr/local/lib/libopencv_video.so.3.0.0
compare_daft: /usr/local/lib/libopencv_highgui.so.3.0.0
compare_daft: /usr/local/lib/libopencv_videoio.so.3.0.0
compare_daft: /usr/local/lib/libopencv_imgcodecs.so.3.0.0
compare_daft: /usr/local/lib/libopencv_imgproc.so.3.0.0
compare_daft: /usr/local/lib/libopencv_core.so.3.0.0
compare_daft: CMakeFiles/compare_daft.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable compare_daft"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/compare_daft.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/compare_daft.dir/build: compare_daft
.PHONY : CMakeFiles/compare_daft.dir/build

CMakeFiles/compare_daft.dir/requires: CMakeFiles/compare_daft.dir/main.cpp.o.requires
CMakeFiles/compare_daft.dir/requires: CMakeFiles/compare_daft.dir/transform.cpp.o.requires
.PHONY : CMakeFiles/compare_daft.dir/requires

CMakeFiles/compare_daft.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/compare_daft.dir/cmake_clean.cmake
.PHONY : CMakeFiles/compare_daft.dir/clean

CMakeFiles/compare_daft.dir/depend:
	cd /home/frederik/pcl/gabor_recall/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/frederik/pcl/gabor_recall /home/frederik/pcl/gabor_recall /home/frederik/pcl/gabor_recall/build /home/frederik/pcl/gabor_recall/build /home/frederik/pcl/gabor_recall/build/CMakeFiles/compare_daft.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/compare_daft.dir/depend

