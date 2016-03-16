Message("CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")

project(sqlite3)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB LIB_SOURCES *.c)
file(GLOB LIB_HEADERS *.h)
add_library(sqlite3 ${LIB_SOURCES} ${LIB_HEADERS})