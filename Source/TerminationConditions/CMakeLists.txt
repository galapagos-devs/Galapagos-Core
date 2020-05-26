#include(CMakeSwig.cmake)
set(SRCS
        fitness_threshold.h
        fitness_threshold.cpp)

set(BOOTSTRAP
        termination_condition_bootstrap.cpp)

add_library(StaticTerminationConditions OBJECT ${SRCS})
set_target_properties(StaticTerminationConditions PROPERTIES
        OUTPUT_NAME ${SOURCE_NAME}${NAME_DELIMITER}${TERMINATION_CONDITIONS_NAME})

add_library(SharedTerminationConditions SHARED ${BOOTSTRAP})
target_link_libraries(SharedTerminationConditions StaticTerminationConditions)
set_target_properties(SharedTerminationConditions PROPERTIES
        OUTPUT_NAME ${SOURCE_NAME}${NAME_DELIMITER}${TERMINATION_CONDITIONS_NAME})
