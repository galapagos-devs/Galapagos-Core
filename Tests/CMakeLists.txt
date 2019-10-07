include(../External/Catch/Catch.cmake)
#include(../Source)

#set(SOURCE_LIBS)
add_subdirectory(Unit)

add_executable(tests
  $<TARGET_OBJECTS:SelectionAlgorithms>
  $<TARGET_OBJECTS:TerminationConditions>
  $<TARGET_OBJECTS:galapagos>
  $<TARGET_OBJECTS:Unit>
  #${SOURCE_LIBS}
  test_runner.cpp
)

catch_discover_tests(tests)
