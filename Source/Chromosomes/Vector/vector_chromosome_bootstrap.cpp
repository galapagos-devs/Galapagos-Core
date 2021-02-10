#include <typeindex>

#include "../../API/galapagos.h"
#include "../../API/genetic_factory.h"

#include "API/vector_chromosome.h"

#include "../../stochastic_internal.h"
#include "kpoint_crossover.h"
#include "gaussian_mutation.h"
#include "randomization_mutation.h"


GALAPAGOS_BOOTSTRAP(genetic_factory*& factory) {
    stochastic_internal& stochastic_instance = stochastic_internal::get_instance();

    GALAPAGOS_REGISTER_OBJ(factory, chromosome, vector_chromosome, stochastic_instance);
    GALAPAGOS_REGISTER_OBJ(factory, crossover, kpoint_crossover, stochastic_instance);
    GALAPAGOS_REGISTER_OBJ(factory, mutation, gaussian_mutation, stochastic_instance);
    GALAPAGOS_REGISTER_OBJ(factory, mutation, randomization_mutation, stochastic_instance);
}