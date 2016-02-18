# Install script for directory: /home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/3th_party/jsoncpp-1.6.5/include

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/json/assertions.h;/usr/local/include/json/autolink.h;/usr/local/include/json/config.h;/usr/local/include/json/features.h;/usr/local/include/json/forwards.h;/usr/local/include/json/json.h;/usr/local/include/json/reader.h;/usr/local/include/json/value.h;/usr/local/include/json/version.h;/usr/local/include/json/writer.h")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/usr/local/include/json" TYPE FILE FILES
    "/home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/3th_party/jsoncpp-1.6.5/include/json/assertions.h"
    "/home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/3th_party/jsoncpp-1.6.5/include/json/autolink.h"
    "/home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/3th_party/jsoncpp-1.6.5/include/json/config.h"
    "/home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/3th_party/jsoncpp-1.6.5/include/json/features.h"
    "/home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/3th_party/jsoncpp-1.6.5/include/json/forwards.h"
    "/home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/3th_party/jsoncpp-1.6.5/include/json/json.h"
    "/home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/3th_party/jsoncpp-1.6.5/include/json/reader.h"
    "/home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/3th_party/jsoncpp-1.6.5/include/json/value.h"
    "/home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/3th_party/jsoncpp-1.6.5/include/json/version.h"
    "/home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/3th_party/jsoncpp-1.6.5/include/json/writer.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

