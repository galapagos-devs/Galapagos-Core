%module termination_conditions
%{
#include "fitness_threshold.h"
%}

%import "../galapagos.swg"

%ignore fitness_threshold;
%include "fitness_threshold.h"
