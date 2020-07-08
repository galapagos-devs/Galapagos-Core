#include "fitness_threshold.h"
#include "../API/population.h"
#include "../API/creature.h"

bool fitness_threshold::operator()(const population* population) const {
    return invoke(population);
}

bool fitness_threshold::invoke(const population* population) const {
    creature* optimal_creature = population->get_optimal_creature();
    return optimal_creature->get_fitness() >= _metadata->fitness_threshold;
}
