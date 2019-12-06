set(SRCS
  fitness_threshold.h
  fitness_threshold.cpp)

if(BUILD_STATIC_LIBS)
  add_library(StaticTerminationConditions OBJECT ${SRCS})
  set_target_properties(StaticTerminationConditions PROPERTIES
    OUTPUT_NAME ${SOURCE_NAME}${NAME_DELIMITER}${TERMINATION_CONDITIONS_NAME})
endif()

if(BUILD_SHARED_LIBS)
  add_library(SharedTerminationConditions SHARED ${SRCS})
  set_target_properties(SharedTerminationConditions PROPERTIES
    OUTPUT_NAME ${SOURCE_NAME}${NAME_DELIMITER}${TERMINATION_CONDITIONS_NAME})

endif()
