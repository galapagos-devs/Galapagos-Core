# project metadata
cmake_minimum_required(VERSION 3.15)
project(Galapagos)

####
# CMake Configuration
####

# Output Directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Build Options
option(BUILD_SHARED_LIBS "Build the shared libraries." ON)
option(BUILD_STATIC_LIBS "Build the static libraries." OFF)
option(BUILD_TESTS "Build the test executable." OFF)

# File names
set(SOURCE_NAME Galapagos
        CACHE INTERNAL
        "Name of the lib built from the `Source` directory")

set(CHROMOSOMES_NAME Chromosomes
        CACHE INTERNAL
        "Name of the lib built from the `Source/Chromosomes` director")

set(CROSSOVERS_NAME Crossovers
        CACHE INTERNAL
        "Name of the lib built from the `Source/Crossovers` director")

set(SELECTION_ALGORITHMS_NAME SelectionAlgorithms
        CACHE INTERNAL
        "Name of the lib built from the `Source/SelectionAlogrithms` directory")

set(TERMINATION_CONDITIONS_NAME TerminationConditions
        CACHE INTERNAL
        "Name of the lib built from the `Source/TerminationConditions` directory")

set(MUTATIONS_NAME Mutations
        CACHE INTERNAL
        "Name of the lib built from the `Source/Mutations` directory")

set(NAME_DELIMITER -
        CACHE INTERNAL
        "The symbol used as a delimiter between Galapagos Satellite libs.")

# C++ Standard
set(CMAKE_CXX_STANDARD 17)

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
