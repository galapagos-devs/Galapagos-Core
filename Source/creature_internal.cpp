#include "API/stochastic.h"

#include "creature_internal.h"
#include "genetic_factory.h"

// Constructor/Destructor
creature_internal::creature_internal(creature_metadata* creature_metadata, stochastic* stochastic_instance) {
    _creature_metadata = creature_metadata;
    _stochastic_instance = stochastic_instance;

    genetic_factory& factory = genetic_factory::get_instance();
    for(size_t i = 0; i < _creature_metadata->num_chromosomes; i++) {
        chromosome_metadata* chromosome_metadata = _creature_metadata->chromosome_metadata[i];
        _chromosomes[chromosome_metadata->name] = factory.create_chromosome(chromosome_metadata);
    }
}

creature_internal::~creature_internal() {
    // Delete all chromosomes
    for(std::map<std::string, chromosome*>::iterator it = _chromosomes.begin(); it != _chromosomes.end(); ++it) {
        delete it->second;
    }
}

// Public methods
double creature_internal::get_fitness() {
    return _creature_metadata->fitness_function(this);
}

creature_internal* creature_internal::breed_with(creature_internal* mate) {
    auto* child = new creature_internal(_creature_metadata, _stochastic_instance);

    for(size_t i = 0; i < _creature_metadata->num_chromosomes; i++) {
        chromosome_metadata* chromosome_metadata = _creature_metadata->chromosome_metadata[i];
        std::string chromosome_name = chromosome_metadata->name;

        // Select crossover & mutation proportional to their weight
        crossover* crossover = _get_crossover(chromosome_metadata->crossover_metadata, chromosome_metadata->num_crossovers);
        mutation* mutation = _get_mutation(chromosome_metadata->mutation_metadata, chromosome_metadata->num_mutations);

        // Conditionally apply cross-over
        chromosome* child_chromosome = get_chromosome<chromosome>(chromosome_name);
        if(_stochastic_instance->evaluate_probability(chromosome_metadata->crossover_rate))
            child_chromosome = crossover->invoke(
                    get_chromosome<chromosome>(chromosome_name), mate->get_chromosome<chromosome>(chromosome_name));

        // Conditionally apply mutation
        if(_stochastic_instance->evaluate_probability(chromosome_metadata->mutation_rate))
            child_chromosome = mutation->invoke(child_chromosome);

        child->_set_chromosome(chromosome_name, child_chromosome);
    }

    return child;
}

// Private methods
template <class TOperator, class TMetadata>
TOperator* creature_internal::_get_genetic_operator(TMetadata** operator_metadata, size_t num_operators,
                                                    create_genetic_operator_a<TOperator, TMetadata> create_genetic_operator) {
    std::vector<TOperator*> genetic_operators;
    double* weights = new double[num_operators];

    for(size_t i = 0; i < num_operators; i++) {
        // populate genetic_operators vector
        TOperator* genetic_operator = create_genetic_operator(operator_metadata[i]);
        genetic_operators.push_back(genetic_operator);

        // populate weights list
        weights[i] = genetic_operator->get_weight();
    }

    size_t chosen_index = _stochastic_instance->weight_proportionate_selection(weights, num_operators);

    for(size_t i = 0; i < num_operators; i++) {  // memory clean up
        if(i != chosen_index)
            delete genetic_operators[i];
    }

    return genetic_operators[chosen_index];
}

crossover* creature_internal::_get_crossover(crossover_metadata** metadata, size_t num_crossovers) {
    genetic_factory& factory = genetic_factory::get_instance();
    create_genetic_operator_a<crossover, crossover_metadata>  create_crossover = [&factory](crossover_metadata* metadatai) {
        return factory.create_crossover(metadatai);
    };
    return _get_genetic_operator<crossover, crossover_metadata>(metadata, num_crossovers, create_crossover);
}

mutation* creature_internal::_get_mutation(mutation_metadata** metadata, size_t num_mutations) {
    genetic_factory& factory = genetic_factory::get_instance();
    create_genetic_operator_a<mutation, mutation_metadata>  create_mutation = [&factory](mutation_metadata* metadatai) {
        return factory.create_mutation(metadatai);
    };
    return _get_genetic_operator<mutation, mutation_metadata>(metadata, num_mutations, create_mutation);
}

void creature_internal::_set_chromosome(std::string name, chromosome* new_chromosome) {
    delete _chromosomes[name];
    _chromosomes[name] = new_chromosome;
}
