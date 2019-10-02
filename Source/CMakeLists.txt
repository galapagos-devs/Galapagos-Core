add_subdirectory(SelectionAlgorithms)
add_subdirectory(TerminationConditions)

add_library(galapagos STATIC
  galapagos.cpp
  population.cpp
  stochastic.cpp
  Factory/genetic_factory.cpp
  $<TARGET_OBJECTS:SelectionAlgorithms>
  $<TARGET_OBJECTS:TerminationConditions>
)

set(SOURCE_LIBS
  $<TARGET_OBJECTS:SelectionAlgorithms>
  $<TARGET_OBJECTS:galapagos>
)
