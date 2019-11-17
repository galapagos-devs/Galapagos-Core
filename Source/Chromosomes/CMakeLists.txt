set(CHROMOSOMES_NAME Chromosome)

set(SRCS
        vector_chromosome.h)

if(BUILD_STATIC_LIBS)
    add_library(StaticChromosomes OBJECT ${SRCS})
    set_target_properties(StaticChromosomes PROPERTIES
            OUTPUT_NAME ${SOURCE_NAME}${NAME_DELIMITER}${CHROMOSOMES_NAME})
endif()

if(BUILD_SHARED_LIBS)
    add_library(SharedChromosomes SHARED ${SRCS})
    set_target_properties(SharedChromosomes PROPERTIES
            OUTPUT_NAME ${SOURCE_NAME}${NAME_DELIMITER}${CHROMOSOMES_NAME})
endif()