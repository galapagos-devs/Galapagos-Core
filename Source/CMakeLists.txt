add_subdirectory(SelectionAlgorithms)
add_subdirectory(TerminationConditions)

set(SRCS
  galapagos.cpp
  population.cpp
  stochastic.cpp
  Factory/genetic_factory.cpp
)

if(BUILD_STATIC_LIBS)
  add_library(StaticGalapagos STATIC ${SRCS})
  target_link_libraries(StaticGalapagos
    $<TARGET_OBJECTS:StaticSelectionAlgorithms>
    $<TARGET_OBJECTS:StaticTerminationConditions>
  )
endif()

if(BUILD_SHARED_LIBS)
  add_library(SharedGalapagos SHARED ${SRCS})
endif()
