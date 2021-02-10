#include <typeindex>

#include "../API/galapagos.h"
#include "../API/genetic_factory.h"

#include "fitness_threshold.h"

GALAPAGOS_BOOTSTRAP(genetic_factory*& factory) {
    GALAPAGOS_REGISTER_OBJ(factory, termination_condition, fitness_threshold);
}