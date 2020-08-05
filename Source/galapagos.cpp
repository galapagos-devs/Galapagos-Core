#include "API/galapagos.h"

#include "API/genetic_factory.h"
#include "galapagos_assemblies.h"
#include "population_internal.h"
#include "stochastic_internal.h"

GALAPAGOS_BOOTSTRAP genetic_factory* gc_bootstrap() {
    stochastic_internal& stochastic_instance = stochastic_internal::get_instance();
    genetic_factory& factory = genetic_factory::get_instance();

    factory.register_population(std::type_index(typeid(population_metadata)),
            [&stochastic_instance](const population_metadata& metadata) {
        return new population_internal(metadata, stochastic_instance);
    }, [](population* population) { delete population; });

    factory.register_creature(std::type_index(typeid(creature_metadata)),
            [&stochastic_instance](const creature_metadata& metadata) {
        return new creature_internal(metadata, stochastic_instance);
    }, [](creature* creature) { delete creature; });

    return &factory;
}
