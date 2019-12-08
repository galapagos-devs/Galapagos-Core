set(SRCS
        kpoint_crossover.h
        kpoint_crossover.cpp)

if (BUILD_STATIC_LIBS)
    add_library(StaticCrossOvers OBJECT ${SRCS})
    set_target_properties(StaticCrossOvers
            PROPERTIES
            OUTPUT_NAME ${SOURCE_NAME}${NAME_DELIMITER}${CROSSOVERS_NAME})
endif ()

if (BUILD_SHARED_LIBS)
    add_library(SharedCrossOvers SHARED ${SRCS})
    set_target_properties(SharedCrossOvers
            PROPERTIES
            OUTPUT_NAME ${SOURCE_NAME}${NAME_DELIMITER}${CROSSOVERS_NAME})
endif ()
