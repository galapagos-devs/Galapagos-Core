set(SRCS
  fitness_threshold.h
  fitness_threshold.cpp
)

if(BUILD_STATIC_LIBS)
  add_library(StaticTerminationConditions OBJECT ${SRCS})
endif()

if(BUILD_SHARED_LIBS)
  add_library(SharedTerminationConditions SHARED ${SRCS})
endif()
