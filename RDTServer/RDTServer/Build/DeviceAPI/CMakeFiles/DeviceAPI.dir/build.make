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

# Include any dependencies generated for this target.
include DeviceAPI/CMakeFiles/DeviceAPI.dir/depend.make

# Include the progress variables for this target.
include DeviceAPI/CMakeFiles/DeviceAPI.dir/progress.make

# Include the compile flags for this target's objects.
include DeviceAPI/CMakeFiles/DeviceAPI.dir/flags.make

DeviceAPI/cotire/DeviceAPI_CXX_prefix.hxx.gch: DeviceAPI/cotire/DeviceAPI_CXX_prefix.hxx
DeviceAPI/cotire/DeviceAPI_CXX_prefix.hxx.gch: DeviceAPI/cotire/DeviceAPI_CXX_prefix.hxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Building CXX precompiled header DeviceAPI/cotire/DeviceAPI_CXX_prefix.hxx.gch"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI && /usr/bin/cmake -DCOTIRE_BUILD_TYPE:STRING=Release -DCOTIRE_VERBOSE:BOOL=$(VERBOSE) -P /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/CMake/cotire.cmake precompile /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI/DeviceAPI_CXX_cotire.cmake /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI/cotire/DeviceAPI_CXX_prefix.hxx /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI/cotire/DeviceAPI_CXX_prefix.hxx.gch /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/BinraryRDTClientCommand.cpp

DeviceAPI/cotire/DeviceAPI_CXX_prefix.hxx: DeviceAPI/cotire/DeviceAPI_CXX_prefix.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating CXX prefix header DeviceAPI/cotire/DeviceAPI_CXX_prefix.hxx"
	/usr/bin/cmake -DCOTIRE_BUILD_TYPE:STRING=Release -DCOTIRE_VERBOSE:BOOL=$(VERBOSE) -P /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/CMake/cotire.cmake combine /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI/DeviceAPI_CXX_cotire.cmake /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI/cotire/DeviceAPI_CXX_prefix.hxx /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI/cotire/DeviceAPI_CXX_prefix.cxx

DeviceAPI/cotire/DeviceAPI_CXX_prefix.cxx: ../DeviceAPI/PrefixHeader.pch
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating CXX prefix source DeviceAPI/cotire/DeviceAPI_CXX_prefix.cxx"
	/usr/bin/cmake -DCOTIRE_BUILD_TYPE:STRING=Release -DCOTIRE_VERBOSE:BOOL=$(VERBOSE) -P /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/CMake/cotire.cmake combine /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI/DeviceAPI_CXX_cotire.cmake /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI/cotire/DeviceAPI_CXX_prefix.cxx /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/PrefixHeader.pch

DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientCommand.cpp.o: DeviceAPI/CMakeFiles/DeviceAPI.dir/flags.make
DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientCommand.cpp.o: ../DeviceAPI/BinraryRDTClientCommand.cpp
DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientCommand.cpp.o: DeviceAPI/cotire/DeviceAPI_CXX_prefix.hxx.gch
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientCommand.cpp.o"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/DeviceAPI.dir/BinraryRDTClientCommand.cpp.o -c /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/BinraryRDTClientCommand.cpp

DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientCommand.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DeviceAPI.dir/BinraryRDTClientCommand.cpp.i"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/BinraryRDTClientCommand.cpp > CMakeFiles/DeviceAPI.dir/BinraryRDTClientCommand.cpp.i

DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientCommand.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DeviceAPI.dir/BinraryRDTClientCommand.cpp.s"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/BinraryRDTClientCommand.cpp -o CMakeFiles/DeviceAPI.dir/BinraryRDTClientCommand.cpp.s

DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientCommand.cpp.o.requires:
.PHONY : DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientCommand.cpp.o.requires

DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientCommand.cpp.o.provides: DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientCommand.cpp.o.requires
	$(MAKE) -f DeviceAPI/CMakeFiles/DeviceAPI.dir/build.make DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientCommand.cpp.o.provides.build
.PHONY : DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientCommand.cpp.o.provides

DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientCommand.cpp.o.provides.build: DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientCommand.cpp.o

DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientConnect.cpp.o: DeviceAPI/CMakeFiles/DeviceAPI.dir/flags.make
DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientConnect.cpp.o: ../DeviceAPI/BinraryRDTClientConnect.cpp
DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientConnect.cpp.o: DeviceAPI/cotire/DeviceAPI_CXX_prefix.hxx.gch
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientConnect.cpp.o"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/DeviceAPI.dir/BinraryRDTClientConnect.cpp.o -c /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/BinraryRDTClientConnect.cpp

DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientConnect.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DeviceAPI.dir/BinraryRDTClientConnect.cpp.i"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/BinraryRDTClientConnect.cpp > CMakeFiles/DeviceAPI.dir/BinraryRDTClientConnect.cpp.i

DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientConnect.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DeviceAPI.dir/BinraryRDTClientConnect.cpp.s"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/BinraryRDTClientConnect.cpp -o CMakeFiles/DeviceAPI.dir/BinraryRDTClientConnect.cpp.s

DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientConnect.cpp.o.requires:
.PHONY : DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientConnect.cpp.o.requires

DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientConnect.cpp.o.provides: DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientConnect.cpp.o.requires
	$(MAKE) -f DeviceAPI/CMakeFiles/DeviceAPI.dir/build.make DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientConnect.cpp.o.provides.build
.PHONY : DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientConnect.cpp.o.provides

DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientConnect.cpp.o.provides.build: DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientConnect.cpp.o

DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerCommand.cpp.o: DeviceAPI/CMakeFiles/DeviceAPI.dir/flags.make
DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerCommand.cpp.o: ../DeviceAPI/BinraryRDTServerCommand.cpp
DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerCommand.cpp.o: DeviceAPI/cotire/DeviceAPI_CXX_prefix.hxx.gch
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerCommand.cpp.o"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/DeviceAPI.dir/BinraryRDTServerCommand.cpp.o -c /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/BinraryRDTServerCommand.cpp

DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerCommand.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DeviceAPI.dir/BinraryRDTServerCommand.cpp.i"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/BinraryRDTServerCommand.cpp > CMakeFiles/DeviceAPI.dir/BinraryRDTServerCommand.cpp.i

DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerCommand.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DeviceAPI.dir/BinraryRDTServerCommand.cpp.s"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/BinraryRDTServerCommand.cpp -o CMakeFiles/DeviceAPI.dir/BinraryRDTServerCommand.cpp.s

DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerCommand.cpp.o.requires:
.PHONY : DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerCommand.cpp.o.requires

DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerCommand.cpp.o.provides: DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerCommand.cpp.o.requires
	$(MAKE) -f DeviceAPI/CMakeFiles/DeviceAPI.dir/build.make DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerCommand.cpp.o.provides.build
.PHONY : DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerCommand.cpp.o.provides

DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerCommand.cpp.o.provides.build: DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerCommand.cpp.o

DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerConnect.cpp.o: DeviceAPI/CMakeFiles/DeviceAPI.dir/flags.make
DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerConnect.cpp.o: ../DeviceAPI/BinraryRDTServerConnect.cpp
DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerConnect.cpp.o: DeviceAPI/cotire/DeviceAPI_CXX_prefix.hxx.gch
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerConnect.cpp.o"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/DeviceAPI.dir/BinraryRDTServerConnect.cpp.o -c /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/BinraryRDTServerConnect.cpp

DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerConnect.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DeviceAPI.dir/BinraryRDTServerConnect.cpp.i"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/BinraryRDTServerConnect.cpp > CMakeFiles/DeviceAPI.dir/BinraryRDTServerConnect.cpp.i

DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerConnect.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DeviceAPI.dir/BinraryRDTServerConnect.cpp.s"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/BinraryRDTServerConnect.cpp -o CMakeFiles/DeviceAPI.dir/BinraryRDTServerConnect.cpp.s

DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerConnect.cpp.o.requires:
.PHONY : DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerConnect.cpp.o.requires

DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerConnect.cpp.o.provides: DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerConnect.cpp.o.requires
	$(MAKE) -f DeviceAPI/CMakeFiles/DeviceAPI.dir/build.make DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerConnect.cpp.o.provides.build
.PHONY : DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerConnect.cpp.o.provides

DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerConnect.cpp.o.provides.build: DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerConnect.cpp.o

DeviceAPI/CMakeFiles/DeviceAPI.dir/Command.cpp.o: DeviceAPI/CMakeFiles/DeviceAPI.dir/flags.make
DeviceAPI/CMakeFiles/DeviceAPI.dir/Command.cpp.o: ../DeviceAPI/Command.cpp
DeviceAPI/CMakeFiles/DeviceAPI.dir/Command.cpp.o: DeviceAPI/cotire/DeviceAPI_CXX_prefix.hxx.gch
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object DeviceAPI/CMakeFiles/DeviceAPI.dir/Command.cpp.o"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/DeviceAPI.dir/Command.cpp.o -c /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/Command.cpp

DeviceAPI/CMakeFiles/DeviceAPI.dir/Command.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DeviceAPI.dir/Command.cpp.i"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/Command.cpp > CMakeFiles/DeviceAPI.dir/Command.cpp.i

DeviceAPI/CMakeFiles/DeviceAPI.dir/Command.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DeviceAPI.dir/Command.cpp.s"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/Command.cpp -o CMakeFiles/DeviceAPI.dir/Command.cpp.s

DeviceAPI/CMakeFiles/DeviceAPI.dir/Command.cpp.o.requires:
.PHONY : DeviceAPI/CMakeFiles/DeviceAPI.dir/Command.cpp.o.requires

DeviceAPI/CMakeFiles/DeviceAPI.dir/Command.cpp.o.provides: DeviceAPI/CMakeFiles/DeviceAPI.dir/Command.cpp.o.requires
	$(MAKE) -f DeviceAPI/CMakeFiles/DeviceAPI.dir/build.make DeviceAPI/CMakeFiles/DeviceAPI.dir/Command.cpp.o.provides.build
.PHONY : DeviceAPI/CMakeFiles/DeviceAPI.dir/Command.cpp.o.provides

DeviceAPI/CMakeFiles/DeviceAPI.dir/Command.cpp.o.provides.build: DeviceAPI/CMakeFiles/DeviceAPI.dir/Command.cpp.o

DeviceAPI/CMakeFiles/DeviceAPI.dir/Connect.cpp.o: DeviceAPI/CMakeFiles/DeviceAPI.dir/flags.make
DeviceAPI/CMakeFiles/DeviceAPI.dir/Connect.cpp.o: ../DeviceAPI/Connect.cpp
DeviceAPI/CMakeFiles/DeviceAPI.dir/Connect.cpp.o: DeviceAPI/cotire/DeviceAPI_CXX_prefix.hxx.gch
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object DeviceAPI/CMakeFiles/DeviceAPI.dir/Connect.cpp.o"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/DeviceAPI.dir/Connect.cpp.o -c /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/Connect.cpp

DeviceAPI/CMakeFiles/DeviceAPI.dir/Connect.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DeviceAPI.dir/Connect.cpp.i"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/Connect.cpp > CMakeFiles/DeviceAPI.dir/Connect.cpp.i

DeviceAPI/CMakeFiles/DeviceAPI.dir/Connect.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DeviceAPI.dir/Connect.cpp.s"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/Connect.cpp -o CMakeFiles/DeviceAPI.dir/Connect.cpp.s

DeviceAPI/CMakeFiles/DeviceAPI.dir/Connect.cpp.o.requires:
.PHONY : DeviceAPI/CMakeFiles/DeviceAPI.dir/Connect.cpp.o.requires

DeviceAPI/CMakeFiles/DeviceAPI.dir/Connect.cpp.o.provides: DeviceAPI/CMakeFiles/DeviceAPI.dir/Connect.cpp.o.requires
	$(MAKE) -f DeviceAPI/CMakeFiles/DeviceAPI.dir/build.make DeviceAPI/CMakeFiles/DeviceAPI.dir/Connect.cpp.o.provides.build
.PHONY : DeviceAPI/CMakeFiles/DeviceAPI.dir/Connect.cpp.o.provides

DeviceAPI/CMakeFiles/DeviceAPI.dir/Connect.cpp.o.provides.build: DeviceAPI/CMakeFiles/DeviceAPI.dir/Connect.cpp.o

DeviceAPI/CMakeFiles/DeviceAPI.dir/Device.cpp.o: DeviceAPI/CMakeFiles/DeviceAPI.dir/flags.make
DeviceAPI/CMakeFiles/DeviceAPI.dir/Device.cpp.o: ../DeviceAPI/Device.cpp
DeviceAPI/CMakeFiles/DeviceAPI.dir/Device.cpp.o: DeviceAPI/cotire/DeviceAPI_CXX_prefix.hxx.gch
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object DeviceAPI/CMakeFiles/DeviceAPI.dir/Device.cpp.o"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/DeviceAPI.dir/Device.cpp.o -c /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/Device.cpp

DeviceAPI/CMakeFiles/DeviceAPI.dir/Device.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DeviceAPI.dir/Device.cpp.i"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/Device.cpp > CMakeFiles/DeviceAPI.dir/Device.cpp.i

DeviceAPI/CMakeFiles/DeviceAPI.dir/Device.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DeviceAPI.dir/Device.cpp.s"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/Device.cpp -o CMakeFiles/DeviceAPI.dir/Device.cpp.s

DeviceAPI/CMakeFiles/DeviceAPI.dir/Device.cpp.o.requires:
.PHONY : DeviceAPI/CMakeFiles/DeviceAPI.dir/Device.cpp.o.requires

DeviceAPI/CMakeFiles/DeviceAPI.dir/Device.cpp.o.provides: DeviceAPI/CMakeFiles/DeviceAPI.dir/Device.cpp.o.requires
	$(MAKE) -f DeviceAPI/CMakeFiles/DeviceAPI.dir/build.make DeviceAPI/CMakeFiles/DeviceAPI.dir/Device.cpp.o.provides.build
.PHONY : DeviceAPI/CMakeFiles/DeviceAPI.dir/Device.cpp.o.provides

DeviceAPI/CMakeFiles/DeviceAPI.dir/Device.cpp.o.provides.build: DeviceAPI/CMakeFiles/DeviceAPI.dir/Device.cpp.o

DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTClientCommand.cpp.o: DeviceAPI/CMakeFiles/DeviceAPI.dir/flags.make
DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTClientCommand.cpp.o: ../DeviceAPI/JsonRDTClientCommand.cpp
DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTClientCommand.cpp.o: DeviceAPI/cotire/DeviceAPI_CXX_prefix.hxx.gch
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/CMakeFiles $(CMAKE_PROGRESS_11)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTClientCommand.cpp.o"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/DeviceAPI.dir/JsonRDTClientCommand.cpp.o -c /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/JsonRDTClientCommand.cpp

DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTClientCommand.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DeviceAPI.dir/JsonRDTClientCommand.cpp.i"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/JsonRDTClientCommand.cpp > CMakeFiles/DeviceAPI.dir/JsonRDTClientCommand.cpp.i

DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTClientCommand.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DeviceAPI.dir/JsonRDTClientCommand.cpp.s"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/JsonRDTClientCommand.cpp -o CMakeFiles/DeviceAPI.dir/JsonRDTClientCommand.cpp.s

DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTClientCommand.cpp.o.requires:
.PHONY : DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTClientCommand.cpp.o.requires

DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTClientCommand.cpp.o.provides: DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTClientCommand.cpp.o.requires
	$(MAKE) -f DeviceAPI/CMakeFiles/DeviceAPI.dir/build.make DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTClientCommand.cpp.o.provides.build
.PHONY : DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTClientCommand.cpp.o.provides

DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTClientCommand.cpp.o.provides.build: DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTClientCommand.cpp.o

DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTCommand.cpp.o: DeviceAPI/CMakeFiles/DeviceAPI.dir/flags.make
DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTCommand.cpp.o: ../DeviceAPI/JsonRDTCommand.cpp
DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTCommand.cpp.o: DeviceAPI/cotire/DeviceAPI_CXX_prefix.hxx.gch
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/CMakeFiles $(CMAKE_PROGRESS_12)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTCommand.cpp.o"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/DeviceAPI.dir/JsonRDTCommand.cpp.o -c /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/JsonRDTCommand.cpp

DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTCommand.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DeviceAPI.dir/JsonRDTCommand.cpp.i"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/JsonRDTCommand.cpp > CMakeFiles/DeviceAPI.dir/JsonRDTCommand.cpp.i

DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTCommand.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DeviceAPI.dir/JsonRDTCommand.cpp.s"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/JsonRDTCommand.cpp -o CMakeFiles/DeviceAPI.dir/JsonRDTCommand.cpp.s

DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTCommand.cpp.o.requires:
.PHONY : DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTCommand.cpp.o.requires

DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTCommand.cpp.o.provides: DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTCommand.cpp.o.requires
	$(MAKE) -f DeviceAPI/CMakeFiles/DeviceAPI.dir/build.make DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTCommand.cpp.o.provides.build
.PHONY : DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTCommand.cpp.o.provides

DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTCommand.cpp.o.provides.build: DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTCommand.cpp.o

DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTServerCommand.cpp.o: DeviceAPI/CMakeFiles/DeviceAPI.dir/flags.make
DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTServerCommand.cpp.o: ../DeviceAPI/JsonRDTServerCommand.cpp
DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTServerCommand.cpp.o: DeviceAPI/cotire/DeviceAPI_CXX_prefix.hxx.gch
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/CMakeFiles $(CMAKE_PROGRESS_13)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTServerCommand.cpp.o"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/DeviceAPI.dir/JsonRDTServerCommand.cpp.o -c /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/JsonRDTServerCommand.cpp

DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTServerCommand.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DeviceAPI.dir/JsonRDTServerCommand.cpp.i"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/JsonRDTServerCommand.cpp > CMakeFiles/DeviceAPI.dir/JsonRDTServerCommand.cpp.i

DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTServerCommand.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DeviceAPI.dir/JsonRDTServerCommand.cpp.s"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/JsonRDTServerCommand.cpp -o CMakeFiles/DeviceAPI.dir/JsonRDTServerCommand.cpp.s

DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTServerCommand.cpp.o.requires:
.PHONY : DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTServerCommand.cpp.o.requires

DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTServerCommand.cpp.o.provides: DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTServerCommand.cpp.o.requires
	$(MAKE) -f DeviceAPI/CMakeFiles/DeviceAPI.dir/build.make DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTServerCommand.cpp.o.provides.build
.PHONY : DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTServerCommand.cpp.o.provides

DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTServerCommand.cpp.o.provides.build: DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTServerCommand.cpp.o

DeviceAPI/CMakeFiles/DeviceAPI.dir/UTF.cpp.o: DeviceAPI/CMakeFiles/DeviceAPI.dir/flags.make
DeviceAPI/CMakeFiles/DeviceAPI.dir/UTF.cpp.o: ../DeviceAPI/UTF.cpp
DeviceAPI/CMakeFiles/DeviceAPI.dir/UTF.cpp.o: DeviceAPI/cotire/DeviceAPI_CXX_prefix.hxx.gch
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/CMakeFiles $(CMAKE_PROGRESS_14)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object DeviceAPI/CMakeFiles/DeviceAPI.dir/UTF.cpp.o"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/DeviceAPI.dir/UTF.cpp.o -c /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/UTF.cpp

DeviceAPI/CMakeFiles/DeviceAPI.dir/UTF.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DeviceAPI.dir/UTF.cpp.i"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/UTF.cpp > CMakeFiles/DeviceAPI.dir/UTF.cpp.i

DeviceAPI/CMakeFiles/DeviceAPI.dir/UTF.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DeviceAPI.dir/UTF.cpp.s"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/UTF.cpp -o CMakeFiles/DeviceAPI.dir/UTF.cpp.s

DeviceAPI/CMakeFiles/DeviceAPI.dir/UTF.cpp.o.requires:
.PHONY : DeviceAPI/CMakeFiles/DeviceAPI.dir/UTF.cpp.o.requires

DeviceAPI/CMakeFiles/DeviceAPI.dir/UTF.cpp.o.provides: DeviceAPI/CMakeFiles/DeviceAPI.dir/UTF.cpp.o.requires
	$(MAKE) -f DeviceAPI/CMakeFiles/DeviceAPI.dir/build.make DeviceAPI/CMakeFiles/DeviceAPI.dir/UTF.cpp.o.provides.build
.PHONY : DeviceAPI/CMakeFiles/DeviceAPI.dir/UTF.cpp.o.provides

DeviceAPI/CMakeFiles/DeviceAPI.dir/UTF.cpp.o.provides.build: DeviceAPI/CMakeFiles/DeviceAPI.dir/UTF.cpp.o

DeviceAPI/CMakeFiles/DeviceAPI.dir/Utility.cpp.o: DeviceAPI/CMakeFiles/DeviceAPI.dir/flags.make
DeviceAPI/CMakeFiles/DeviceAPI.dir/Utility.cpp.o: ../DeviceAPI/Utility.cpp
DeviceAPI/CMakeFiles/DeviceAPI.dir/Utility.cpp.o: DeviceAPI/cotire/DeviceAPI_CXX_prefix.hxx.gch
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/CMakeFiles $(CMAKE_PROGRESS_15)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object DeviceAPI/CMakeFiles/DeviceAPI.dir/Utility.cpp.o"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/DeviceAPI.dir/Utility.cpp.o -c /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/Utility.cpp

DeviceAPI/CMakeFiles/DeviceAPI.dir/Utility.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DeviceAPI.dir/Utility.cpp.i"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/Utility.cpp > CMakeFiles/DeviceAPI.dir/Utility.cpp.i

DeviceAPI/CMakeFiles/DeviceAPI.dir/Utility.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DeviceAPI.dir/Utility.cpp.s"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI/Utility.cpp -o CMakeFiles/DeviceAPI.dir/Utility.cpp.s

DeviceAPI/CMakeFiles/DeviceAPI.dir/Utility.cpp.o.requires:
.PHONY : DeviceAPI/CMakeFiles/DeviceAPI.dir/Utility.cpp.o.requires

DeviceAPI/CMakeFiles/DeviceAPI.dir/Utility.cpp.o.provides: DeviceAPI/CMakeFiles/DeviceAPI.dir/Utility.cpp.o.requires
	$(MAKE) -f DeviceAPI/CMakeFiles/DeviceAPI.dir/build.make DeviceAPI/CMakeFiles/DeviceAPI.dir/Utility.cpp.o.provides.build
.PHONY : DeviceAPI/CMakeFiles/DeviceAPI.dir/Utility.cpp.o.provides

DeviceAPI/CMakeFiles/DeviceAPI.dir/Utility.cpp.o.provides.build: DeviceAPI/CMakeFiles/DeviceAPI.dir/Utility.cpp.o

# Object files for target DeviceAPI
DeviceAPI_OBJECTS = \
"CMakeFiles/DeviceAPI.dir/BinraryRDTClientCommand.cpp.o" \
"CMakeFiles/DeviceAPI.dir/BinraryRDTClientConnect.cpp.o" \
"CMakeFiles/DeviceAPI.dir/BinraryRDTServerCommand.cpp.o" \
"CMakeFiles/DeviceAPI.dir/BinraryRDTServerConnect.cpp.o" \
"CMakeFiles/DeviceAPI.dir/Command.cpp.o" \
"CMakeFiles/DeviceAPI.dir/Connect.cpp.o" \
"CMakeFiles/DeviceAPI.dir/Device.cpp.o" \
"CMakeFiles/DeviceAPI.dir/JsonRDTClientCommand.cpp.o" \
"CMakeFiles/DeviceAPI.dir/JsonRDTCommand.cpp.o" \
"CMakeFiles/DeviceAPI.dir/JsonRDTServerCommand.cpp.o" \
"CMakeFiles/DeviceAPI.dir/UTF.cpp.o" \
"CMakeFiles/DeviceAPI.dir/Utility.cpp.o"

# External object files for target DeviceAPI
DeviceAPI_EXTERNAL_OBJECTS =

../lib/libDeviceAPI.a: DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientCommand.cpp.o
../lib/libDeviceAPI.a: DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientConnect.cpp.o
../lib/libDeviceAPI.a: DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerCommand.cpp.o
../lib/libDeviceAPI.a: DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerConnect.cpp.o
../lib/libDeviceAPI.a: DeviceAPI/CMakeFiles/DeviceAPI.dir/Command.cpp.o
../lib/libDeviceAPI.a: DeviceAPI/CMakeFiles/DeviceAPI.dir/Connect.cpp.o
../lib/libDeviceAPI.a: DeviceAPI/CMakeFiles/DeviceAPI.dir/Device.cpp.o
../lib/libDeviceAPI.a: DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTClientCommand.cpp.o
../lib/libDeviceAPI.a: DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTCommand.cpp.o
../lib/libDeviceAPI.a: DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTServerCommand.cpp.o
../lib/libDeviceAPI.a: DeviceAPI/CMakeFiles/DeviceAPI.dir/UTF.cpp.o
../lib/libDeviceAPI.a: DeviceAPI/CMakeFiles/DeviceAPI.dir/Utility.cpp.o
../lib/libDeviceAPI.a: DeviceAPI/CMakeFiles/DeviceAPI.dir/build.make
../lib/libDeviceAPI.a: DeviceAPI/CMakeFiles/DeviceAPI.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library ../../lib/libDeviceAPI.a"
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && $(CMAKE_COMMAND) -P CMakeFiles/DeviceAPI.dir/cmake_clean_target.cmake
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DeviceAPI.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
DeviceAPI/CMakeFiles/DeviceAPI.dir/build: ../lib/libDeviceAPI.a
.PHONY : DeviceAPI/CMakeFiles/DeviceAPI.dir/build

DeviceAPI/CMakeFiles/DeviceAPI.dir/requires: DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientCommand.cpp.o.requires
DeviceAPI/CMakeFiles/DeviceAPI.dir/requires: DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTClientConnect.cpp.o.requires
DeviceAPI/CMakeFiles/DeviceAPI.dir/requires: DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerCommand.cpp.o.requires
DeviceAPI/CMakeFiles/DeviceAPI.dir/requires: DeviceAPI/CMakeFiles/DeviceAPI.dir/BinraryRDTServerConnect.cpp.o.requires
DeviceAPI/CMakeFiles/DeviceAPI.dir/requires: DeviceAPI/CMakeFiles/DeviceAPI.dir/Command.cpp.o.requires
DeviceAPI/CMakeFiles/DeviceAPI.dir/requires: DeviceAPI/CMakeFiles/DeviceAPI.dir/Connect.cpp.o.requires
DeviceAPI/CMakeFiles/DeviceAPI.dir/requires: DeviceAPI/CMakeFiles/DeviceAPI.dir/Device.cpp.o.requires
DeviceAPI/CMakeFiles/DeviceAPI.dir/requires: DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTClientCommand.cpp.o.requires
DeviceAPI/CMakeFiles/DeviceAPI.dir/requires: DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTCommand.cpp.o.requires
DeviceAPI/CMakeFiles/DeviceAPI.dir/requires: DeviceAPI/CMakeFiles/DeviceAPI.dir/JsonRDTServerCommand.cpp.o.requires
DeviceAPI/CMakeFiles/DeviceAPI.dir/requires: DeviceAPI/CMakeFiles/DeviceAPI.dir/UTF.cpp.o.requires
DeviceAPI/CMakeFiles/DeviceAPI.dir/requires: DeviceAPI/CMakeFiles/DeviceAPI.dir/Utility.cpp.o.requires
.PHONY : DeviceAPI/CMakeFiles/DeviceAPI.dir/requires

DeviceAPI/CMakeFiles/DeviceAPI.dir/clean:
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI && $(CMAKE_COMMAND) -P CMakeFiles/DeviceAPI.dir/cmake_clean.cmake
.PHONY : DeviceAPI/CMakeFiles/DeviceAPI.dir/clean

DeviceAPI/CMakeFiles/DeviceAPI.dir/depend: DeviceAPI/cotire/DeviceAPI_CXX_prefix.hxx.gch
DeviceAPI/CMakeFiles/DeviceAPI.dir/depend: DeviceAPI/cotire/DeviceAPI_CXX_prefix.hxx
DeviceAPI/CMakeFiles/DeviceAPI.dir/depend: DeviceAPI/cotire/DeviceAPI_CXX_prefix.cxx
	cd /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/Build/DeviceAPI/CMakeFiles/DeviceAPI.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : DeviceAPI/CMakeFiles/DeviceAPI.dir/depend

