enable_testing()
include(../External/Catch/Catch.cmake)

add_subdirectory(Integration)
add_subdirectory(Unit)

add_executable(tests
    $<TARGET_OBJECTS:Integration>
    $<TARGET_OBJECTS:Unit>
    test_runner.cpp)

target_link_libraries(tests
    $<TARGET_OBJECTS:StaticVectorChromosome>
    $<TARGET_OBJECTS:StaticSelectionAlgorithms>
    $<TARGET_OBJECTS:StaticTerminationConditions>)

catch_discover_tests(tests)
