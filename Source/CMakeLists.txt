set(SRCS
        creature_internal.cpp
        galapagos_bootstrap.cpp
        population_internal.cpp)

add_library(SharedGalapagos SHARED ${SRCS})
set_target_properties(SharedGalapagos PROPERTIES
        OUTPUT_NAME ${SOURCE_NAME})

if(BUILD_SWIG)
    include(CMakeSwig.cmake)
endif()

add_subdirectory(Chromosomes)
add_subdirectory(SelectionAlgorithms)
add_subdirectory(TerminationConditions)