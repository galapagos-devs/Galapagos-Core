set(SRCS
        permutation_chromosome.cpp)

set(BOOTSTRAP
        permutation_chromosome_bootstrap.cpp)

add_library(StaticPermutationChromosome OBJECT ${SRCS})
set_target_properties(StaticPermutationChromosome PROPERTIES
        OUTPUT_NAME ${SOURCE_NAME}${NAME_DELIMITER}${CHROMOSOMES_NAME}${NAME_DELIMITER}Permutation)

add_library(SharedPermutationChromosome SHARED ${BOOTSTRAP})
target_link_libraries(SharedPermutationChromosome StaticPermutationChromosome)
set_target_properties(SharedPermutationChromosome PROPERTIES
        OUTPUT_NAME ${SOURCE_NAME}${NAME_DELIMITER}${CHROMOSOMES_NAME}${NAME_DELIMITER}Permutation)