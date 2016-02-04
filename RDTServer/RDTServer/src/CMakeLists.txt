Message("CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")

project(RDTServer)
#project(RDTServer C CXX)

###################### Solar #############################
set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../CMake")
include(Solar)

Message("CMAKE_TARGET_ARCHITECTURES = ${CMAKE_TARGET_ARCHITECTURES}")
###################### Solar #############################

###################### CXX11 #############################
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
elseif(DEFINED ENV{IPHUB})
    message("...using cross compile to IP-hub")
	CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()
###################### CXX11 #############################

###################### Base #############################
#set(DEBUG_FLAGS "-g -O0 -Wall")
#set(RELEASE_FLAGS "-O3")
#
#set(CMAKE_CXX_FLAGS ${RELEASE_FLAGS})
#set(CMAKE_C_FLAGS ${RELEASE_FLAGS})
#
#set(CMAKE_CXX_FLAGS_DEBUG ${DEBUG_FLAGS})
#set(CMAKE_CXX_FLAGS_DEBUG ${GCOV_FLAGS})
#set(CMAKE_C_FLAGS_DEBUG ${DEBUG_FLAGS})
#set(CMAKE_C_FLAGS_DEBUG ${GCOV_FLAGS})
#set(CMAKE_EXE_LINKER_FLAGS_DEBUG ${GCOV_FLAGS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../TUTK_Kalay_Platform_SDK_2.1.3/Include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../3th_party/jsoncpp-1.6.5/include)

Message("CMAKE_SYSTEM_NAME = ${CMAKE_SYSTEM_NAME}")
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../build/3th_party/jsoncpp-1.6.5/src/lib_json)
if (CMAKE_SYSTEM_NAME MATCHES "WIN32")
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../TUTK_Kalay_Platform_SDK_2.1.3/Lib/Windows/Win32/x64)
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../TUTK_Kalay_Platform_SDK_2.1.3/Lib/MAC)
elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
    if (CMAKE_TARGET_ARCHITECTURES MATCHES "i386")
		link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../3th_party/unix_socket)
        link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../TUTK_Kalay_Platform_SDK_2.1.3/Lib/Linux/x86)
    elseif (CMAKE_TARGET_ARCHITECTURES MATCHES "x86_64")
        link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../TUTK_Kalay_Platform_SDK_2.1.3/Lib/Linux/x64)
	elseif(DEFINED ENV{IPHUB})
		message("...using IP-hub library")
		link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../TUTK_Kalay_Platform_SDK_2.1.3/Lib/Linux/Vtech_IPHub)
    endif()
endif()

find_package (Threads)

#file( GLOB LIB_SOURCES *.cpp )
#file( GLOB LIB_HEADERS *.h )
#add_library( YourLib ${LIB_SOURCES} ${LIB_HEADERS} )

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
    Message("SRC_FILES = ${SRC_FILES}")
add_executable(RDTServer ${SRC_FILES})

if (CMAKE_SYSTEM_NAME MATCHES "WIN32")
    target_link_libraries(RDTServer RDTAPIs jsoncpp)
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    target_link_libraries(RDTServer IOTCAPIs_ALL jsoncpp)
elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
#    target_link_libraries(RDTServer RDTAPIs IOTCAPIs pthread jsoncpp)
    target_link_libraries(RDTServer RDTAPIs IOTCAPIs pthread jsoncpp socket++)
endif()
###################### Base #############################

######################## cotire ###########################
include(cotire)

# enable warnings
Message("CMAKE_CXX_COMPILER_ID = ${CMAKE_CXX_COMPILER_ID}")
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set_target_properties(RDTServer PROPERTIES COMPILE_FLAGS "/Wall")
    set_target_properties(RDTServer PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "PrefixHeader.pch")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set_target_properties(RDTServer PROPERTIES COMPILE_FLAGS "-Weverything")
    set_target_properties(RDTServer PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "PrefixHeader.pch")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set_target_properties(RDTServer PROPERTIES COMPILE_FLAGS "-Wall -Wextra")
    set_target_properties(RDTServer PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "PrefixHeader.pch")
endif()

cotire(RDTServer)

# cotire sets the following properties
get_target_property(_unitySource RDTServer COTIRE_CXX_UNITY_SOURCE)
get_target_property(_prefixHeader RDTServer COTIRE_CXX_PREFIX_HEADER)
get_target_property(_precompiledHeader RDTServer COTIRE_CXX_PRECOMPILED_HEADER)
get_target_property(_unityTargetName RDTServer COTIRE_UNITY_TARGET_NAME)

if (_unitySource)
    message(STATUS "RDTServer unity source: ${_unitySource}")
endif()

if (_prefixHeader)
    message(STATUS "RDTServer prefix header: ${_prefixHeader}")
endif()

if (_precompiledHeader)
    message(STATUS "RDTServer precompiled header: ${_precompiledHeader}")
endif()

if (TARGET ${_unityTargetName})
    message(STATUS "RDTServer unity target: ${_unityTargetName}")
endif()
###################### cotire #############################
