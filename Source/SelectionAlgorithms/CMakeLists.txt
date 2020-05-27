include(CMakeSwig.cmake)
set(SRCS
        tournament_selection.h
        tournament_selection.cpp)

set(BOOTSTRAP
        selection_algorithm_bootstrap.cpp)

add_library(StaticSelectionAlgorithms OBJECT ${SRCS})
set_target_properties(StaticSelectionAlgorithms PROPERTIES
        OUTPUT_NAME ${SOURCE_NAME}${NAME_DELIMITER}${SELECTION_ALGORITHMS_NAME})

add_library(SharedSelectionAlgorithms SHARED ${BOOTSTRAP})
target_link_libraries(SharedSelectionAlgorithms StaticSelectionAlgorithms)
set_target_properties(SharedSelectionAlgorithms PROPERTIES
        OUTPUT_NAME ${SOURCE_NAME}${NAME_DELIMITER}${SELECTION_ALGORITHMS_NAME})
