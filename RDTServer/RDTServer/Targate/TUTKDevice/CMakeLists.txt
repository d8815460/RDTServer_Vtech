Message("CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")

project(TUTKDevice)

###################### Base #############################
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../DeviceAPI)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../../TUTK_Kalay_Platform_SDK_2.1.3/Include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../3th_party/curlpp/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../3th_party/jsoncpp-1.6.5/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../3th_party/sqlite-amalgamation-3110100)

if (CMAKE_TARGET_ARCHITECTURES MATCHES "arm")
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../3th_party/libcurl/arm)
endif()


Message("CMAKE_SYSTEM_NAME = ${CMAKE_SYSTEM_NAME}")
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
link_directories(${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
if (CMAKE_SYSTEM_NAME MATCHES "WIN32")
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../../TUTK_Kalay_Platform_SDK_2.1.3/Lib/Windows/Win32/x64)
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../../TUTK_Kalay_Platform_SDK_2.1.3/Lib/MAC)
elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
    if (CMAKE_TARGET_ARCHITECTURES MATCHES "i386")
        link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../../TUTK_Kalay_Platform_SDK_2.1.3/Lib/Linux/x86)
    elseif (CMAKE_TARGET_ARCHITECTURES MATCHES "x86_64")
        link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../../TUTK_Kalay_Platform_SDK_2.1.3/Lib/Linux/x64)
    elseif (CMAKE_TARGET_ARCHITECTURES MATCHES "arm")
        link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../../TUTK_Kalay_Platform_SDK_2.1.3/Lib/Linux/Vtech_IPHub)
    endif()
endif()

file(GLOB_RECURSE SRC_FILES *.cpp)
    Message("SRC_FILES = ${SRC_FILES}")
add_executable(TUTKDevice ${SRC_FILES})

if (CMAKE_SYSTEM_NAME MATCHES "WIN32")
    target_link_libraries(TUTKDevice DeviceAPI RDTAPIs curlpp jsoncpp sqlite3 dl)
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    target_link_libraries(TUTKDevice DeviceAPI IOTCAPIs_ALL curlpp jsoncpp sqlite3 dl)
elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_link_libraries(TUTKDevice DeviceAPI RDTAPIs IOTCAPIs pthread curlpp jsoncpp sqlite3 dl)
endif()

###################### Base #############################

######################## cotire ###########################
# cotire sets the following properties
get_target_property(_unitySource DeviceAPI COTIRE_CXX_UNITY_SOURCE)
get_target_property(_prefixHeader DeviceAPI COTIRE_CXX_PREFIX_HEADER)
get_target_property(_precompiledHeader DeviceAPI COTIRE_CXX_PRECOMPILED_HEADER)
get_target_property(_unityTargetName DeviceAPI COTIRE_UNITY_TARGET_NAME)

if (_unitySource)
    message(STATUS "DeviceAPI unity source: ${_unitySource}")
endif()

if (_prefixHeader)
    message(STATUS "DeviceAPI prefix header: ${_prefixHeader}")
endif()

if (_precompiledHeader)
    message(STATUS "DeviceAPI precompiled header: ${_precompiledHeader}")
endif()

if (TARGET ${_unityTargetName})
    message(STATUS "DeviceAPI unity target: ${_unityTargetName}")
endif()

set_target_properties(TUTKDevice PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "${_prefixHeader}")
cotire(TUTKDevice)
###################### cotire #############################
