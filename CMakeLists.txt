cmake_minimum_required(VERSION 3.15)
project(Galapagos)

add_subdirectory(Source)

add_library(galapagos SHARED $<TARGET_OBJECTS:Source>)
