Message("CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")

cmake_minimum_required(VERSION 2.8.12.2)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

###################### Disable warnings #############################
macro(add_lldb_definitions)
  # We don't want no semicolons on LLDB_DEFINITIONS:
  foreach(arg ${ARGN})
    set(LLDB_DEFINITIONS "${LLVM_DEFINITIONS} ${arg}")
  endforeach(arg)
  add_definitions( ${ARGN} )
endmacro(add_lldb_definitions)

# Disable Clang warnings
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  add_lldb_definitions(
    -Wno-deprecated-declarations # Suppress "deprecated auto_ptr" warnings
  )
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "3.3")
  add_lldb_definitions(
    -Wno-deprecated-register # Suppress "deprecated register keyword" warnings
  )
endif()

# Disable MSVC warnings
if( MSVC )
  add_lldb_definitions(
    -wd4018 # Suppress 'warning C4018: '>=' : signed/unsigned mismatch'
    -wd4068 # Suppress 'warning C4068: unknown pragma'
    -wd4150 # Suppress 'warning C4150: deletion of pointer to incomplete type'
    -wd4521 # Suppress 'warning C4521: 'type' : multiple copy constructors specified'
  )
endif()
###################### Disable warnings #############################

###################### cotire #############################
include(cotire)
###################### cotire #############################

###################### Solar #############################
include(Solar)
###################### Solar #############################

Message("CMAKE_SYSTEM_NAME = ${CMAKE_SYSTEM_NAME}")
Message("CMAKE_TARGET_ARCHITECTURES = ${CMAKE_TARGET_ARCHITECTURES}")

# arm架構設定env IPHUB
if (CMAKE_TARGET_ARCHITECTURES MATCHES "arm")
	set(ENV{IPHUB} 1)
endif()

if (CMAKE_SYSTEM_NAME MATCHES "WIN32")
	set(LIB lib/win32)
	set(BIN bin/win32)
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
	set(LIB lib/mac)
	set(BIN bin/mac)
elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
	if (CMAKE_TARGET_ARCHITECTURES MATCHES "i386")
        set(LIB lib/linux/i386)
		set(BIN bin/linux/i386)
    elseif (CMAKE_TARGET_ARCHITECTURES MATCHES "x86_64")
        set(LIB lib/linux/x86_64)
		set(BIN bin/linux/x86_64)
	elseif (CMAKE_TARGET_ARCHITECTURES MATCHES "arm")
		set(LIB lib/linux/arm)
		set(BIN bin/linux/arm)
    endif()
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${LIB})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${LIB})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${BIN})

###################### CXX11 #############################
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()
###################### CXX11 #############################

add_subdirectory(3th_party/sqlite-amalgamation-3110100)
add_subdirectory(3th_party/curlpp)
add_subdirectory(3th_party/jsoncpp-1.6.5)
add_subdirectory(DeviceAPI)
add_subdirectory(Targate/TUTKDevice)
add_subdirectory(Targate/VtechDevice)
add_subdirectory(Targate/VtechHardwardDevice)
