# Install script for directory: /Users/jakey/Documents/SyncData/Repository/TUTK/RDTServer/RDTServer/RDTServer/3th_party/jsoncpp-1.6.5/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/jakey/Documents/SyncData/Repository/TUTK/RDTServer/RDTServer/RDTServer/build/3th_party/jsoncpp-1.6.5/src/lib_json/cmake_install.cmake")
  include("/Users/jakey/Documents/SyncData/Repository/TUTK/RDTServer/RDTServer/RDTServer/build/3th_party/jsoncpp-1.6.5/src/jsontestrunner/cmake_install.cmake")
  include("/Users/jakey/Documents/SyncData/Repository/TUTK/RDTServer/RDTServer/RDTServer/build/3th_party/jsoncpp-1.6.5/src/test_lib_json/cmake_install.cmake")

endif()

