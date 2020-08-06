set(SRCS
        creature_internal.h
        creature_internal.cpp
        galapagos_bootstrap.cpp
        API/genetic_factory.h
        population_internal.h
        population_internal.cpp
        stochastic_internal.h
        thread_pool.h)

add_library(SharedGalapagos SHARED ${SRCS})
set_target_properties(SharedGalapagos PROPERTIES
        OUTPUT_NAME ${SOURCE_NAME})

if(BUILD_SWIG)
    include(CMakeSwig.cmake)
endif()

add_subdirectory(Chromosomes)
add_subdirectory(SelectionAlgorithms)
add_subdirectory(TerminationConditions)