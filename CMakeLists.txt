# project metadata
cmake_minimum_required(VERSION 3.15)
project(Galapagos)

####
# CMake Configuration
####
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# build control
#set(BUILD_SWIG TRUE)
set(BUILD_SWIG FALSE)
set(BUILD_TESTS TRUE)

# Output Directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)  # was `bin/archive`
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)  # was `bin/library`
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)  # was `bin/runtime`

# File names
set(SOURCE_NAME Galapagos
        CACHE INTERNAL
        "Name of the lib built from the `Source` directory")

set(CHROMOSOMES_NAME Chromosomes
        CACHE INTERNAL
        "Name of the lib built from the `Source/Chromosomes` director")

set(SELECTION_ALGORITHMS_NAME SelectionAlgorithms
        CACHE INTERNAL
        "Name of the lib built from the `Source/SelectionAlgorithms` directory")

set(TERMINATION_CONDITIONS_NAME TerminationConditions
        CACHE INTERNAL
        "Name of the lib built from the `Source/TerminationConditions` directory")

set(NAME_DELIMITER -
        CACHE INTERNAL
        "The symbol used as a delimiter between Galapagos Satellite libs.")

# C++ Standard
set(CMAKE_CXX_STANDARD 17)

# SWIG
if(BUILD_SWIG)
    include(CMakeSwig.cmake)
endif()

# Source
add_subdirectory(Source)

# Tests
if(BUILD_TESTS)
    add_subdirectory(Tests)
endif()
