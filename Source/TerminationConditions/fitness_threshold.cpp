#include "fitness_threshold.h"
#include "../API/population.h"
#include "../API/creature.h"

fitness_threshold::fitness_threshold(size_t fitness_threshold) {
  _fitness_threshold = fitness_threshold;
}

fitness_threshold::~fitness_threshold() {

}

bool fitness_threshold::operator()(population* population) {
  return invoke(population);
}

bool fitness_threshold::invoke(population* population) {
  creature* optimal_creature = population->get_optimal_creature();
  return optimal_creature->get_fitness() >= _fitness_threshold;
}

GALAPAGOS_API fitness_threshold_metadata* create_fitness_threshold_metadata() {
  return new fitness_threshold_metadata();
}

GALAPAGOS_API void delete_fitness_threshold_metadata(fitness_threshold_metadata* fitness_threshold_metadata) {
  delete fitness_threshold_metadata;
}

GALAPAGOS_API void set_fitness_threshold_metadata_fitness_threshold(fitness_threshold_metadata* fitness_threshold_metadata, size_t fitness_threshold) {
    fitness_threshold_metadata->fitness_threshold = fitness_threshold;
}

GALAPAGOS_API size_t get_fitness_threshold_metadata_fitness_threshold(fitness_threshold_metadata* fitness_threshold_metadata) {
  return fitness_threshold_metadata->fitness_threshold;
}
