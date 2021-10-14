#include <typeindex>

#include "../../API/galapagos.h"
#include "../../API/genetic_factory.h"

#include "API/permutation_chromosome.h"

#include "../../stochastic_internal.h"

GALAPAGOS_BOOTSTRAP(genetic_factory*& factory) {
    stochastic_internal& stochastic_instance = stochastic_internal::get_instance();

    GALAPAGOS_REGISTER_OBJ(factory, chromosome, permutation_chromosome, stochastic_instance);
}

