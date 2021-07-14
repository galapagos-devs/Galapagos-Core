# project metadata
set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.15)
project(Galapagos)

####
# CMake Configuration
####
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# build control
set(BUILD_SWIG  FALSE)
set(BUILD_TESTS TRUE)
set(ENABLE_CLANG_TIDY TRUE)

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
#set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-fms-compatibility")

if(ENABLE_CLANG_TIDY)
    find_program(CLANGTIDY clang-tidy)
    if(CLANGTIDY)
        set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
        set(CMAKE_CXX_CLANG_TIDY "${CLANGTIDY}")
#        set(CMAKE_CXX_CLANG_TIDY "${CLANGTIDY};--fix")
#                "${CLANGTIDY};--extra-arg-before=-std=c++18;--extra-arg-before=-stdlib=libc++;--extra-arg=-Wno-unknown-warning-option;--extra-arg-before=-fms-compatibility;--header-filter=${CMAKE_SOURCE_DIR}/src/*")
#                "${CLANGTIDY};--extra-arg-before=-std=c++17;--extra-arg-before=--driver-mode=cl")
    else()
        message(SEND_ERROR "clang-tidy requested but executable not found")
    endif()
endif()
#set(CMAKE_CXX_CLANG_TIDY "clang-tidy;--extra-arg-before=-std=c++17;-header-filter=.*;${CLANG_TIDY_ARGS}")

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
