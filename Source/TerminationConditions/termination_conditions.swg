%module termination_conditions
%{
#include "fitness_threshold.h"
%}

%import "../galapagos.swg"

struct fitness_threshold_metadata : termination_condition_metadata {
    size_t fitness_threshold;
};
