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
