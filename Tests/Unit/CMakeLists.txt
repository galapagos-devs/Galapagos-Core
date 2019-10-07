add_library(Unit OBJECT
  selection_algorithm_tests.cpp
  termination_condition_tests.cpp
)

# list(TEST_LIBS APPEND
#   $<TARGET_OBJECTS:Unit>
# )
