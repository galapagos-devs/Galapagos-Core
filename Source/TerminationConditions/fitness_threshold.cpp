#include "fitness_threshold.h"
#include "../API/population.h"
#include "../API/creature.h"

bool fitness_threshold::invoke(const population* const population) const {
    const std::shared_ptr<creature> optimal_creature = population->get_optimal_creature();
    return optimal_creature->get_fitness() >= _metadata.fitness_threshold;
}
