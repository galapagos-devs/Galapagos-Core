"""
This file is for testing SWIG integration with Galapagos.
It needs to be placed and run inside of the `bin` directory with all the SWIG/CMake artifacts present.
"""
from pathlib import Path
import sys
sys.path.append('.')

from selection_algorithms import tournament_selection_metadata
from termination_conditions import fitness_threshold_metadata
from galapagos import (population_metadata_t,
                       creature_metadata_t,
                       gc_create_population,
                       gc_delete_population)
from vector_chromosome import (gc_get_vector_chromosome,
                               vector_chromosome_metadata,
                               kpoint_crossover_metadata,
                               gaussian_mutation_metadata,
                               randomization_mutation_metadata)

# region Creating Metadata

log_file = Path('galapagos.log')
chromosome_name = "X"


def log_function(log_entry):
    log_file.write_text(f'generation: {log_entry.generation} optimal-fitness: {log_entry.optimal_fitness}\n')


def fitness_function(creature):
    chromosome = gc_get_vector_chromosome(creature, chromosome_name)
    return chromosome.get_gene(0) - chromosome.get_gene(1) + chromosome.get_gene(2)


population_metadata1 = population_metadata_t(
    log_function=log_function,
    size=25, survival_rate=0.25, distance_threshold=0, cooperative_coevolution=False,
    selection_algorithm_metadata=[tournament_selection_metadata(tournament_size=2)],
    termination_condition_metadata=[fitness_threshold_metadata(fitness_threshold=1500)],
    creature_metadata=creature_metadata_t(
        fitness_function, vector_chromosome_metadata(
            name=chromosome_name,
            crossover_rate=1, crossover_metadata=[kpoint_crossover_metadata(weight=1, cut_points=1)],
            mutation_rate=0.5, mutation_metadata=[
                randomization_mutation_metadata(weight=1),
                gaussian_mutation_metadata(weight=4, mean=0, standard_deviation=50)
            ],
            norm_rank=1, size=3, gene_infimum=-500, gene_supremum=500)
    )
)

# endregion


# region Invoke Algorithm Against Metadata

population1 = gc_create_population(population_metadata1)
population1.evolve()

optimal_creature = population1.get_optimal_creature()
optimal_chromosome = gc_get_vector_chromosome(optimal_creature, chromosome_name)

assert optimal_chromosome.get_gene(0) == optimal_chromosome.gene_sup()
assert optimal_chromosome.get_gene(1) == optimal_chromosome.gene_inf()
assert optimal_chromosome.get_gene(2) == optimal_chromosome.gene_sup()

gc_delete_population(population1)

# endregion