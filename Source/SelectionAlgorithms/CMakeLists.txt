set(SRCS
  tournament_selection.h
  tournament_selection.cpp)

if(BUILD_STATIC_LIBS)
  add_library(StaticSelectionAlgorithms OBJECT ${SRCS})
endif()

if(BUILD_SHARED_LIBS)
  add_library(SharedSelectionAlgorithms SHARED ${SRCS})
endif()
