if(BUILD_SWIG)
    include(CMakeSwig.cmake)
endif()
set(SRCS
        gaussian_mutation.cpp
        kpoint_crossover.cpp
        randomization_mutation.cpp
        vector_chromosome.cpp)

set(BOOTSTRAP
        vector_chromosome_bootstrap.cpp)

add_library(StaticVectorChromosome OBJECT ${SRCS})
set_target_properties(StaticVectorChromosome PROPERTIES
        OUTPUT_NAME ${SOURCE_NAME}${NAME_DELIMITER}${CHROMOSOMES_NAME}${NAME_DELIMITER}Vector)

add_library(SharedVectorChromosome SHARED ${BOOTSTRAP})
target_link_libraries(SharedVectorChromosome StaticVectorChromosome)
set_target_properties(SharedVectorChromosome PROPERTIES
        OUTPUT_NAME ${SOURCE_NAME}${NAME_DELIMITER}${CHROMOSOMES_NAME}${NAME_DELIMITER}Vector)
