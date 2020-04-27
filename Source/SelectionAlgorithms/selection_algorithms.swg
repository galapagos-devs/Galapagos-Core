%module selection_algorithms
%{
#include "tournament_selection.h"
%}

%import "../galapagos.swg"

%ignore tournament_selection;
%import "tournament_selection.h"

//struct tournament_selection_metadata : selection_algorithm_metadata {
//	const size_t tournament_size;
//};
