# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build

# Utility rule file for jsoncpp_readerwriter_tests.

# Include the progress variables for this target.
include 3th_party/jsoncpp-1.6.5/src/jsontestrunner/CMakeFiles/jsoncpp_readerwriter_tests.dir/progress.make

3th_party/jsoncpp-1.6.5/src/jsontestrunner/CMakeFiles/jsoncpp_readerwriter_tests: 3th_party/jsoncpp-1.6.5/src/jsontestrunner/jsontestrunner_exe
3th_party/jsoncpp-1.6.5/src/jsontestrunner/CMakeFiles/jsoncpp_readerwriter_tests: 3th_party/jsoncpp-1.6.5/src/test_lib_json/jsoncpp_test
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build/3th_party/jsoncpp-1.6.5/src/jsontestrunner && /usr/bin/python2 -B /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/3th_party/jsoncpp-1.6.5/src/jsontestrunner/../../test/runjsontests.py /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build/3th_party/jsoncpp-1.6.5/src/jsontestrunner/jsontestrunner_exe /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/3th_party/jsoncpp-1.6.5/src/jsontestrunner/../../test/data

jsoncpp_readerwriter_tests: 3th_party/jsoncpp-1.6.5/src/jsontestrunner/CMakeFiles/jsoncpp_readerwriter_tests
jsoncpp_readerwriter_tests: 3th_party/jsoncpp-1.6.5/src/jsontestrunner/CMakeFiles/jsoncpp_readerwriter_tests.dir/build.make
.PHONY : jsoncpp_readerwriter_tests

# Rule to build all files generated by this target.
3th_party/jsoncpp-1.6.5/src/jsontestrunner/CMakeFiles/jsoncpp_readerwriter_tests.dir/build: jsoncpp_readerwriter_tests
.PHONY : 3th_party/jsoncpp-1.6.5/src/jsontestrunner/CMakeFiles/jsoncpp_readerwriter_tests.dir/build

3th_party/jsoncpp-1.6.5/src/jsontestrunner/CMakeFiles/jsoncpp_readerwriter_tests.dir/clean:
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build/3th_party/jsoncpp-1.6.5/src/jsontestrunner && $(CMAKE_COMMAND) -P CMakeFiles/jsoncpp_readerwriter_tests.dir/cmake_clean.cmake
.PHONY : 3th_party/jsoncpp-1.6.5/src/jsontestrunner/CMakeFiles/jsoncpp_readerwriter_tests.dir/clean

3th_party/jsoncpp-1.6.5/src/jsontestrunner/CMakeFiles/jsoncpp_readerwriter_tests.dir/depend:
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/3th_party/jsoncpp-1.6.5/src/jsontestrunner /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build/3th_party/jsoncpp-1.6.5/src/jsontestrunner /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build/3th_party/jsoncpp-1.6.5/src/jsontestrunner/CMakeFiles/jsoncpp_readerwriter_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : 3th_party/jsoncpp-1.6.5/src/jsontestrunner/CMakeFiles/jsoncpp_readerwriter_tests.dir/depend

