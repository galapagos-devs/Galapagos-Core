# project metadata
cmake_minimum_required(VERSION 3.15)
project(Galapagos)

####
# CMake Configuration
####

# Output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# add options
option(BUILD_SHARED_LIBS "Build the shared libraries." ON)
option(BUILD_STATIC_LIBS "Build the static libraries." OFF)
option(BUILD_TESTS "Build the test executable." OFF)

# Tests depend on static lib
if(BUILD_TESTS)
  set(BUILD_STATIC_LIBS ON)
endif()

# Source
if(BUILD_SHARED_LIBS OR BUILD_STATIC_LIBS)
  add_subdirectory(Source)
endif()

# Tests
if(BUILD_TESTS)
  add_subdirectory(Tests)
endif()
