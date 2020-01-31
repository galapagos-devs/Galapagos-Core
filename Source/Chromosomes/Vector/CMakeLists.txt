set(SRCS
        gaussian_mutation.h
        gaussian_mutation.cpp
        kpoint_crossover.h
        kpoint_crossover.cpp
        randomization_mutation.h
        randomization_mutation.cpp
        vector_chromosome.h
        vector_chromosome.cpp
        vector_chromosome_bootstrap.cpp)

add_library(SharedVectorChromosome SHARED ${SRCS})
set_target_properties(SharedVectorChromosome PROPERTIES
        OUTPUT_NAME ${SOURCE_NAME}${NAME_DELIMITER}${CHROMOSOMES_NAME}${NAME_DELIMITER}Vector)
