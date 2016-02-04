Message("CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")

cmake_minimum_required(VERSION 2.8.12.2)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

###################### cotire #############################
include(cotire)
###################### cotire #############################

###################### Solar #############################
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
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()
###################### CXX11 #############################

add_subdirectory(3th_party/jsoncpp-1.6.5)
add_subdirectory(DeviceAPI)
add_subdirectory(Main)
