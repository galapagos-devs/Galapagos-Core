#include <typeindex>
#include <utility>

#include "API/galapagos.h"
#include "API/genetic_factory.h"

#include "population_internal.h"
#include "stochastic_internal.h"

GALAPAGOS_BOOTSTRAP(genetic_factory*& factory) {
    stochastic_internal& stochastic_instance = stochastic_internal::get_instance();
    factory = &genetic_factory::get_instance();

    // TODO: Figure out how to incorporate these registerations into the `GALAPAGOS_REGISTER_OBJ` macro.
    factory->register_population(std::type_index(typeid(population_metadata)),
            [&stochastic_instance](population_metadata_ptr metadata) {
        return new population_internal(std::move(metadata), stochastic_instance);
    }, [](population* population) { delete population; });

    factory->register_creature(std::type_index(typeid(creature_metadata)),
            [&stochastic_instance](creature_metadata_ptr metadata) {
        return new creature_internal(std::move(metadata), stochastic_instance);
    }, [](creature* creature) { delete creature; });
}
