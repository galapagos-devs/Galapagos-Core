#ifndef _CHROMOSOME_METADATA_H_
#define _CHROMOSOME_METADATA_H_

#include "galapagos_types.h"
#include "chromosome.h"
#include "population.h"
#include <string>
#include <cstdint>

struct chromosome_metadata {
	std::string name;
	double croosover_rate;
	double mutation_rate;
};

struct bin_chromosome_metadata : chromosome_metadata {
	uint32_t gene_count;
	bin_crossover_t crossovers;
	bin_mutation_t mutations;
};

#endif /* _CHROMOSOME_METADATA_H_ */ 
