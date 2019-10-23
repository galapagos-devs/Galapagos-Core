set(NAME SelectionAlgorithms)

set(SRCS
  tournament_selection.h
  tournament_selection.cpp)

if(BUILD_STATIC_LIBS)
  add_library(StaticSelectionAlgorithms OBJECT ${SRCS})
  set_target_properties(StaticSelectionAlgorithms PROPERTIES
    OUTPUT_NAME ${NAME})
endif()

if(BUILD_SHARED_LIBS)
  add_library(SharedSelectionAlgorithms SHARED ${SRCS})
  set_target_properties(SharedSelectionAlgorithms PROPERTIES
    OUTPUT_NAME ${NAME})
endif()
