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

# Include any dependencies generated for this target.
include Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/depend.make

# Include the progress variables for this target.
include Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/progress.make

# Include the compile flags for this target's objects.
include Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/flags.make

Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.hxx: Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating CXX prefix header Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.hxx"
	/usr/bin/cmake -DCOTIRE_BUILD_TYPE:STRING=Debug -DCOTIRE_VERBOSE:BOOL=$(VERBOSE) -P /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/CMake/cotire.cmake combine /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build/Targate/TUTKDevice/TUTKDevice_CXX_cotire.cmake /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build/Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.hxx /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build/Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.cxx

Targate/TUTKDevice/cotire/TUTKDevice_CXX_unity.cxx: Targate/TUTKDevice/TUTKDevice_CXX_cotire.cmake
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating CXX unity source Targate/TUTKDevice/cotire/TUTKDevice_CXX_unity.cxx"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Targate/TUTKDevice && /usr/bin/cmake -DCOTIRE_BUILD_TYPE:STRING=Debug -DCOTIRE_VERBOSE:BOOL=$(VERBOSE) -P /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/CMake/cotire.cmake unity /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build/Targate/TUTKDevice/TUTKDevice_CXX_cotire.cmake /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build/Targate/TUTKDevice/cotire/TUTKDevice_CXX_unity.cxx

Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.cxx: DeviceAPI/cotire/DeviceAPI_CXX_prefix.hxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating CXX prefix source Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.cxx"
	/usr/bin/cmake -DCOTIRE_BUILD_TYPE:STRING=Debug -DCOTIRE_VERBOSE:BOOL=$(VERBOSE) -P /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/CMake/cotire.cmake combine /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build/Targate/TUTKDevice/TUTKDevice_CXX_cotire.cmake /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build/Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.cxx /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build/DeviceAPI/cotire/DeviceAPI_CXX_prefix.hxx

Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/cotire/TUTKDevice_CXX_unity.cxx.o: Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/flags.make
Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/cotire/TUTKDevice_CXX_unity.cxx.o: Targate/TUTKDevice/cotire/TUTKDevice_CXX_unity.cxx
Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/cotire/TUTKDevice_CXX_unity.cxx.o: Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.hxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/cotire/TUTKDevice_CXX_unity.cxx.o"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build/Targate/TUTKDevice && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS)  -Winvalid-pch -include "/home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build/Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.hxx"  -o CMakeFiles/TUTKDevice_unity.dir/cotire/TUTKDevice_CXX_unity.cxx.o -c /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build/Targate/TUTKDevice/cotire/TUTKDevice_CXX_unity.cxx

Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/cotire/TUTKDevice_CXX_unity.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TUTKDevice_unity.dir/cotire/TUTKDevice_CXX_unity.cxx.i"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build/Targate/TUTKDevice && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS)  -Winvalid-pch -include "/home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build/Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.hxx"  -E /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build/Targate/TUTKDevice/cotire/TUTKDevice_CXX_unity.cxx > CMakeFiles/TUTKDevice_unity.dir/cotire/TUTKDevice_CXX_unity.cxx.i

Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/cotire/TUTKDevice_CXX_unity.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TUTKDevice_unity.dir/cotire/TUTKDevice_CXX_unity.cxx.s"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build/Targate/TUTKDevice && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS)  -Winvalid-pch -include "/home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build/Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.hxx"  -S /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build/Targate/TUTKDevice/cotire/TUTKDevice_CXX_unity.cxx -o CMakeFiles/TUTKDevice_unity.dir/cotire/TUTKDevice_CXX_unity.cxx.s

Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/cotire/TUTKDevice_CXX_unity.cxx.o.requires:
.PHONY : Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/cotire/TUTKDevice_CXX_unity.cxx.o.requires

Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/cotire/TUTKDevice_CXX_unity.cxx.o.provides: Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/cotire/TUTKDevice_CXX_unity.cxx.o.requires
	$(MAKE) -f Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/build.make Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/cotire/TUTKDevice_CXX_unity.cxx.o.provides.build
.PHONY : Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/cotire/TUTKDevice_CXX_unity.cxx.o.provides

Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/cotire/TUTKDevice_CXX_unity.cxx.o.provides.build: Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/cotire/TUTKDevice_CXX_unity.cxx.o

# Object files for target TUTKDevice_unity
TUTKDevice_unity_OBJECTS = \
"CMakeFiles/TUTKDevice_unity.dir/cotire/TUTKDevice_CXX_unity.cxx.o"

# External object files for target TUTKDevice_unity
TUTKDevice_unity_EXTERNAL_OBJECTS =

Targate/TUTKDevice/TUTKDevice: Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/cotire/TUTKDevice_CXX_unity.cxx.o
Targate/TUTKDevice/TUTKDevice: Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/build.make
Targate/TUTKDevice/TUTKDevice: DeviceAPI/libDeviceAPI.a
Targate/TUTKDevice/TUTKDevice: Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable TUTKDevice"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build/Targate/TUTKDevice && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TUTKDevice_unity.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/build: Targate/TUTKDevice/TUTKDevice
.PHONY : Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/build

Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/requires: Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/cotire/TUTKDevice_CXX_unity.cxx.o.requires
.PHONY : Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/requires

Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/clean:
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build/Targate/TUTKDevice && $(CMAKE_COMMAND) -P CMakeFiles/TUTKDevice_unity.dir/cmake_clean.cmake
.PHONY : Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/clean

Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/depend: Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.hxx
Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/depend: Targate/TUTKDevice/cotire/TUTKDevice_CXX_unity.cxx
Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/depend: Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.cxx
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Targate/TUTKDevice /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build/Targate/TUTKDevice /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/build/Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Targate/TUTKDevice/CMakeFiles/TUTKDevice_unity.dir/depend
