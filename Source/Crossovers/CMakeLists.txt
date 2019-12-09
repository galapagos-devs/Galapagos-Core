set(SRCS
        crossover_internal.h
        kpoint_crossover.h
        kpoint_crossover.cpp)

if (BUILD_STATIC_LIBS)
    add_library(StaticCrossovers OBJECT ${SRCS})
    set_target_properties(StaticCrossovers
            PROPERTIES
            OUTPUT_NAME ${SOURCE_NAME}${NAME_DELIMITER}${CROSSOVERS_NAME})
endif ()

if (BUILD_SHARED_LIBS)
    add_library(SharedCrossovers SHARED ${SRCS})
    target_link_libraries(SharedCrossovers
            $<TARGET_OBJECTS:SharedChromosomes>)
    set_target_properties(SharedCrossovers
            PROPERTIES
            OUTPUT_NAME ${SOURCE_NAME}${NAME_DELIMITER}${CROSSOVERS_NAME})
endif ()
