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
CMAKE_BINARY_DIR = /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build

# Utility rule file for TUTKDevice_pch.

# Include the progress variables for this target.
include Targate/TUTKDevice/CMakeFiles/TUTKDevice_pch.dir/progress.make

Targate/TUTKDevice/CMakeFiles/TUTKDevice_pch: Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.hxx.gch

Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.hxx.gch: Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.hxx
Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.hxx.gch: Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.hxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Building CXX precompiled header Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.hxx.gch"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Targate/TUTKDevice && /usr/bin/cmake -DCOTIRE_BUILD_TYPE:STRING=Release -DCOTIRE_VERBOSE:BOOL=$(VERBOSE) -P /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/CMake/cotire.cmake precompile /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/Targate/TUTKDevice/TUTKDevice_CXX_cotire.cmake /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.hxx /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.hxx.gch /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Targate/TUTKDevice/Body.cpp

Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.hxx: Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating CXX prefix header Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.hxx"
	/usr/bin/cmake -DCOTIRE_BUILD_TYPE:STRING=Release -DCOTIRE_VERBOSE:BOOL=$(VERBOSE) -P /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/CMake/cotire.cmake combine /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/Targate/TUTKDevice/TUTKDevice_CXX_cotire.cmake /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.hxx /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.cxx

Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.cxx: DeviceAPI/cotire/DeviceAPI_CXX_prefix.hxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating CXX prefix source Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.cxx"
	/usr/bin/cmake -DCOTIRE_BUILD_TYPE:STRING=Release -DCOTIRE_VERBOSE:BOOL=$(VERBOSE) -P /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/CMake/cotire.cmake combine /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/Targate/TUTKDevice/TUTKDevice_CXX_cotire.cmake /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.cxx /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI/cotire/DeviceAPI_CXX_prefix.hxx

TUTKDevice_pch: Targate/TUTKDevice/CMakeFiles/TUTKDevice_pch
TUTKDevice_pch: Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.hxx.gch
TUTKDevice_pch: Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.hxx
TUTKDevice_pch: Targate/TUTKDevice/cotire/TUTKDevice_CXX_prefix.cxx
TUTKDevice_pch: Targate/TUTKDevice/CMakeFiles/TUTKDevice_pch.dir/build.make
.PHONY : TUTKDevice_pch

# Rule to build all files generated by this target.
Targate/TUTKDevice/CMakeFiles/TUTKDevice_pch.dir/build: TUTKDevice_pch
.PHONY : Targate/TUTKDevice/CMakeFiles/TUTKDevice_pch.dir/build

Targate/TUTKDevice/CMakeFiles/TUTKDevice_pch.dir/clean:
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/Targate/TUTKDevice && $(CMAKE_COMMAND) -P CMakeFiles/TUTKDevice_pch.dir/cmake_clean.cmake
.PHONY : Targate/TUTKDevice/CMakeFiles/TUTKDevice_pch.dir/clean

Targate/TUTKDevice/CMakeFiles/TUTKDevice_pch.dir/depend:
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Targate/TUTKDevice /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/Targate/TUTKDevice /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/Targate/TUTKDevice/CMakeFiles/TUTKDevice_pch.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Targate/TUTKDevice/CMakeFiles/TUTKDevice_pch.dir/depend

