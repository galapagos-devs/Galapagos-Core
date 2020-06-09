"""
This file is for testing SWIG integration with Galapagos.
It needs to be placed and run inside of the `bin` directory with all the SWIG/CMake artifacts present.
"""

from pathlib import Path
# import sys
# sys.path.append('.')  # Add current path to search path, so we can find the local moduels

import galapagos as gc
import selection_algorithms as gc_selection_algorithms
import termination_conditions as gc_termination_conditions
import vector_chromosome as gc_vector_chromosome

log_file = Path('galapagos.log')
# region population metadata
population_metadata1 = gc.population_metadata_t(log_function=lambda entry: log_file.write_text(f'generation: {entry.generation} '
                                                                                               f'optimal-fitness: {entry.optimal_fitness}\n'),
                                                size=25,
                                                survival_rate=0.25,
                                                distance_threshold=0,
                                                cooperative_coevolution=False,
                                                selection_algorithm_metadata=,
                                                termination_condition_metadata=,
                                                creature_metadata=
                                              )
# endregion

# region selection algorithm metadata
tournament_selection_metadata1 = gc_selection_algorithms.tournament_selection_metadata_t()
# endregion

# region termination condition metadata
fitness_threshold_metadata1 = gc_termination_conditions.fitness_threshold_metadata_t()
# endregion

# region creature metadata
creature_metadata1 = gc.creature_metadata_t()
# endregion

# region chromosome metadata
vector_chromosome_metadata1 = gc_vector_chromosome.vector_chromosome_metadata_t()
# endregion

# region crossover metadata
kpoint_crossover_metadata1 = gc_vector_chromosome.kpoint_crossover_metadata_t()
# endregion

# region mutation metadata
randomization_mutation_metadata1 = gc_vector_chromosome.randomization_mutation_metadata_t()

gaussian_mutation_metadata1 = gc_vector_chromosome.gaussian_mutation_metadata_t()
# endregion
