%module vector_chromosome
%{
#include "gaussian_mutation.h"
#include "kpoint_crossover.h"
#include "randomization_mutation.h"
%}

%import "../../galapagos.swg"

%include "vector_chromosome.h"
%include "kpoint_crossover.h"
%include "gaussian_mutation.h"
%include "randomization_mutation.h"