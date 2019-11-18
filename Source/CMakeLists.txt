add_subdirectory(SelectionAlgorithms)
add_subdirectory(TerminationConditions)

set(SRCS
        creature_internal.h
        creature_internal.cpp
        galapagos.cpp
        population_internal.h
        population_internal.cpp
        stochastic_internal.h
        stochastic_internal.cpp
        genetic_factory.cpp)

set(SOURCE_NAME Galapagos)

if(BUILD_STATIC_LIBS)
    add_library(StaticGalapagos STATIC ${SRCS})
    target_link_libraries(StaticGalapagos
            $<TARGET_OBJECTS:StaticSelectionAlgorithms>
            $<TARGET_OBJECTS:StaticTerminationConditions>)
    set_target_properties(StaticGalapagos PROPERTIES
            OUTPUT_NAME ${SOURCE_NAME})
endif()

if(BUILD_SHARED_LIBS)
    add_library(SharedGalapagos SHARED ${SRCS})
    set_target_properties(SharedGalapagos PROPERTIES
            OUTPUT_NAME ${SOURCE_NAME})
endif()
