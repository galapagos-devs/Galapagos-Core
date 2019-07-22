#ifndef _GALAPAGOS_H_
#define _GALAPAGOS_H_

#include <cstdint>

#include "stochastic.h"
#include "galapagos_types.h"
#include "population.h"
#include "population_metadata.h"
#include "creature.h"

class galapagos_session {
public:
	stochastic* stochastic;

public:
	static galapagos_session& get_instance();

	population_metadata* create_population_metadata();

	population* create_population(population_metadata* population_metadata);
};

#define GALAPAGOS_API extern "C" __declspec(dllexport)

GALAPAGOS_API population_metadata* create_population_metadata();

GALAPAGOS_API void set_population_metadata_size(population_metadata* population_metadata, uint32_t size);
GALAPAGOS_API uint32_t get_population_metadata_size(population_metadata* population_metadata);

GALAPAGOS_API void set_population_metadata_survival_rate(population_metadata* population_metadata, uint32_t survival_rate);
GALAPAGOS_API uint32_t get_population_metadata_survival_rate(population_metadata* population_metadata);

GALAPAGOS_API population* create_population(population_metadata* population_metadata);

#endif /* _GALAPAGOS_H_ */
