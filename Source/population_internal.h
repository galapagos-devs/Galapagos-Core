#ifndef _POPULATION_INTERNAL_H_
#define _POPULATION_INTERNAL_H_

#include <vector>
#include <memory>

#include "API/population.h"
#include "API/creature.h"
#include "API/selection_algorithm.h"
#include "API/termination_condition.h"
#include "API/galapagos_metadata.h"
#include "API/stochastic.h"

#include "creature_internal.h"

class population_internal : population {
  /*
    The internal implementation of the population object from the public API.
    */
private:
    const population_metadata* _population_metadata;
    stochastic* _stochastic_instance;
    log_entry _current_log_entry;

    std::vector<std::shared_ptr<creature>> _creatures;
    std::shared_ptr<creature> _optimal_creature;

public:
    population_internal(const population_metadata* population_metadata, stochastic* stochastic_instance);

    // Returns the number of creates in the population.
    [[nodiscard]] size_t get_size() const override;

    creature* operator[] (int i) const override;
    [[nodiscard]] creature* get_creature(int i) const override;

    // Returns the most optimal creature in terms of fitness.
    [[nodiscard]] creature* get_optimal_creature() const override;

    // Progresses the genetic algorithm until the termination conditions are met.
    void evolve() override;

private:
    // Copies the n best creatures into the next generation based on the survival rate as defined in the metadata.
    size_t _elitism(std::vector<std::shared_ptr<creature>>& new_generation);

    // Breeds population_size - surviving_creature_count, new creates from the current population.
    void _breed_new_generation(std::vector<std::shared_ptr<creature>>& new_generation, size_t surviving_creature_count, std::shared_ptr<selection_algorithm> selection_algorithm);

    // Checks if any of the termination conditions have been met.
    bool _has_terminated(std::vector<std::shared_ptr<termination_condition>>& termination_conditions);

    std::shared_ptr<creature> _find_optimal_creature();

    // Creates all the selection algorithms from the population metadata.
    std::vector<std::shared_ptr<selection_algorithm>> _create_selection_algorithms();

    // Creates all the termination conditions from the population metadata.
    std::vector<std::shared_ptr<termination_condition>> _create_termination_conditions();
};

#endif /* _POPULATION_INTERNAL_H_ */
