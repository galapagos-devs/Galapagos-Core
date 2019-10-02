# project metadata
cmake_minimum_required(VERSION 3.15)
project(Galapagos)

include(CTest)

# source
add_subdirectory(Source)

# tests
add_subdirectory(Tests)
