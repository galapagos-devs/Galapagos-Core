set(SRCS
  fitness_threshold.h
  fitness_threshold.cpp
  termination_condition_bootstrap.cpp)

add_library(SharedTerminationConditions SHARED ${SRCS})
set_target_properties(SharedTerminationConditions PROPERTIES
  OUTPUT_NAME ${SOURCE_NAME}${NAME_DELIMITER}${TERMINATION_CONDITIONS_NAME})
