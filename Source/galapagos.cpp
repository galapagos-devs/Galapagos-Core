#include "API/galapagos.h"
#include "API/Factory/genetic_factory.h"
#include "API/stochastic.h"
#include "stochastic.h"

// Implementation of root galapgos "session" object
galapagos_session::galapagos_session()
{
	stochastic_internal* default_rng = new stochastic_internal();
	__stochastic__ = (stochastic*)default_rng;
}

galapagos_session::~galapagos_session()
{
	delete __stochastic__;
}

galapagos_session& galapagos_session::get_instance()
{
	static galapagos_session instance;
	return instance;
}

population_metadata* galapagos_session::create_population_metadata()
{
	return new population_metadata();
}

population* galapagos_session::create_population(population_metadata* population_metadata)
{
	return genetic_factory::create_population(population_metadata);
}

// Exported (.so/.dll) "C-style" interface to the galapagos library
GALAPAGOS_API population_metadata* create_population_metadata()
{
	galapagos_session& session = galapagos_session::get_instance();
	return session.create_population_metadata();
}

GALAPAGOS_API void set_population_metadata_size(population_metadata* population_metadata, size_t size)
{
	population_metadata->size = size;
}

GALAPAGOS_API size_t get_population_metadata_size(population_metadata* population_metadata)
{
	return population_metadata->size;
}

GALAPAGOS_API void set_population_metadata_survival_rate(population_metadata* population_metadata, double survival_rate)
{
	population_metadata->survival_rate = survival_rate;
}

GALAPAGOS_API double get_population_metadata_survival_rate(population_metadata* population_metadata)
{
	return population_metadata->survival_rate;
}

GALAPAGOS_API population* create_population(population_metadata* population_metadata)
{
	galapagos_session& session = galapagos_session::get_instance();
	return session.create_population(population_metadata);
}
