%module selection_algorithms
%{
#include "tournament_selection.h"
%}

%import "../galapagos.swg"

struct tournament_selection_metadata : selection_algorithm_metadata {
	size_t tournament_size;
};
