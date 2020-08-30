#include <typeindex>

#include "../API/galapagos.h"
#include "../API/genetic_factory.h"

#include "../stochastic_internal.h"
#include "tournament_selection.h"

GALAPAGOS_BOOTSTRAP(genetic_factory*& factory) {
    stochastic_internal& stochastic_instance = stochastic_internal::get_instance();

    factory->register_selection_algorithm(std::type_index(typeid(tournament_selection_metadata)),
            [&stochastic_instance](const selection_algorithm_metadata& metadata) {
                const auto& dynamic = dynamic_cast<const tournament_selection_metadata&>(metadata);
                return new tournament_selection(dynamic, stochastic_instance);
    }, [](selection_algorithm* selection_algorithm) { delete selection_algorithm; });
}