include(CTest)
include(../External/Catch/Catch.cmake)

add_subdirectory(Integration)
#add_subdirectory(Unit)

add_executable(tests
  $<TARGET_OBJECTS:Integration>
  #$<TARGET_OBJECTS:Unit>
  test_runner.cpp)

catch_discover_tests(tests)
