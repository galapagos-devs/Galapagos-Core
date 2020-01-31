set(SRCS
        tournament_selection.h
        tournament_selection.cpp
        selection_algorithm_bootstrap.cpp)


add_library(SharedSelectionAlgorithms SHARED ${SRCS})
set_target_properties(SharedSelectionAlgorithms PROPERTIES
        OUTPUT_NAME ${SOURCE_NAME}${NAME_DELIMITER}${SELECTION_ALGORITHMS_NAME})
