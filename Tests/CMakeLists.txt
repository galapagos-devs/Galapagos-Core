include(CTest)
include(../External/Catch/Catch.cmake)

add_subdirectory(Unit)

add_executable(tests
  $<TARGET_OBJECTS:StaticSelectionAlgorithms>
  $<TARGET_OBJECTS:StaticTerminationConditions>
  $<TARGET_OBJECTS:StaticGalapagos>
  $<TARGET_OBJECTS:Unit>
  test_runner.cpp)

catch_discover_tests(tests)
