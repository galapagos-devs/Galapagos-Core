set(SWIG_EXECUTABLE "C:/Program Files (x86)/swigwin-4.0.1/swig")
set(SWIG_SOURCE_FILE_EXTENSIONS ".swg")

find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

set(CMAKE_SWIG_FLAGS "")

find_package(Python
        REQUIRED
        COMPONENTS Interpreter Development)

include_directories(${Python_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set_source_files_properties(api.swg PROPERTIES CPLUSPLUS ON)
set_source_files_properties(api.swg PROPERTIES SWIG_FLAGS "-includeall")

swig_add_library(swig
        LANGUAGE python
        OUTPUT_DIR ${CMAKE_SOURCE_DIR}/bin/swig
        OUTFILE_DIR ${CMAKE_SOURCE_DIR}/bin/swig/sources
        SOURCES api.swg ../galapagos.cpp ../stochastic_internal.cpp ../genetic_factory.cpp ../population_internal.cpp ../creature_internal.cpp)

swig_link_libraries(swig Python::Module Python::Python)