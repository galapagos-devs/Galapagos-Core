#include "fitness_threshold.h"
#include "population.h"
#include "creature.h"

fitness_threshold::fitness_threshold(size_t fitness_threshold) {
  _fitness_threshold = tournament_size;
}

fitness_threshold::~fitness_threshold() {

}

bool fitness_threshold::operator()(population* population) {
  return invoke(population);
}

bool fitness_threshold::invoke(population* population) {
  creature* optimal_creature = population->get_optimal_creature();
  return optimal_creature->get_fitness() >= fitness_threshold;
}
