#include <typeindex>

#include "../API/galapagos.h"
#include "../API/genetic_factory.h"

#include "../stochastic_internal.h"
#include "tournament_selection.h"

GALAPAGOS_BOOTSTRAP(genetic_factory*& factory) {
    stochastic_internal& stochastic_instance = stochastic_internal::get_instance();

    GALAPAGOS_REGISTER_OBJ(factory, selection_algorithm, tournament_selection, stochastic_instance);
}