set(SRCS
        mutation_internal.h
        gaussian_mutation.h
        gaussian_mutation.cpp
        randomization_mutation.h
        randomization_mutation.cpp)

if(BUILD_STATIC_LIBS)
    add_library(StaticMutations OBJECT ${SRCS})
    set_target_properties(StaticMutations PROPERTIES
            OUTPUT_NAME ${SOURCE_NAME}${NAME_DELIMITER}${MUTATIONS_NAME})
endif()

if(BUILD_SHARED_LIBS)
    add_library(SharedMutations SHARED ${SRCS})
    target_link_libraries(SharedMutations
            $<TARGET_OBJECTS:SharedChromosomes>)
    set_target_properties(SharedMutations PROPERTIES
            OUTPUT_NAME ${SOURCE_NAME}${NAME_DELIMITER}${MUTATIONS_NAME})
endif()