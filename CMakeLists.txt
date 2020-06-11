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

# File names
set(SOURCE_NAME Galapagos
        CACHE INTERNAL
        "Name of the lib built from the `Source` directory")

set(CHROMOSOMES_NAME Chromosomes
        CACHE INTERNAL
        "Name of the lib built from the `Source/Chromosomes` director")

set(SELECTION_ALGORITHMS_NAME SelectionAlgorithms
        CACHE INTERNAL
        "Name of the lib built from the `Source/SelectionAlogrithms` directory")

set(TERMINATION_CONDITIONS_NAME TerminationConditions
        CACHE INTERNAL
        "Name of the lib built from the `Source/TerminationConditions` directory")

set(NAME_DELIMITER -
        CACHE INTERNAL
        "The symbol used as a delimiter between Galapagos Satellite libs.")

# C++ Standard
set(CMAKE_CXX_STANDARD 17)

# Source
add_subdirectory(Source)

# Tests
add_subdirectory(Tests)
