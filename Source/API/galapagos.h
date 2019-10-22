#ifndef _GALAPAGOS_H_
#define _GALAPAGOS_H_

#include <cstdint>

#include "galapagos_metadata.h"
#include "population.h"
#include "stochastic.h"

#ifdef WIN32
#define GALAPAGOS_API extern "C" __declspec(dllexport)
#else
#define GALAPAGOS_API extern "C" __attribute__((visibility("default")))
#endif

/**************************
*****Galapagos Session*****
**************************/
GALAPAGOS_API population* create_population(population_metadata* population_metadata);
GALAPAGOS_API void delete_population(population* population);

#endif /* _GALAPAGOS_H_ */
