%module vector_chromosome
%{
#include "gaussian_mutation.h"
#include "kpoint_crossover.h"
#include "randomization_mutation.h"
#include "vector_chromosome.h"
%}

%import "../../galapagos.swg"


extern "C" struct vector_chromosome_metadata : chromosome_metadata {
    uint32_t norm_rank;
    size_t size;
    double gene_infimum;
    double gene_supremum;
};

%template (get_vector_chromosome) creature::get_chromosome<vector_chromosome>;
