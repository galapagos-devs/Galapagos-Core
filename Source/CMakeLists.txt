set(SRCS
        creature_internal.h
        creature_internal.cpp
        galapagos.cpp
        genetic_factory.h
        genetic_factory.cpp
        population_internal.h
        population_internal.cpp
        stochastic_internal.h
        stochastic_internal.cpp)

add_library(SharedGalapagos SHARED ${SRCS})
set_target_properties(SharedGalapagos PROPERTIES
        OUTPUT_NAME ${SOURCE_NAME})

include(CMakeSwig.cmake)

add_subdirectory(Chromosomes)
add_subdirectory(SelectionAlgorithms)
add_subdirectory(TerminationConditions)