add_subdirectory(SelectionAlgorithms)

add_library(Source OBJECT
  galapagos.cpp
  population.cpp
  stochastic.cpp
  Factory/genetic_factory.cpp
  $<TARGET_OBJECTS:SelectionAlgorithms>
)
