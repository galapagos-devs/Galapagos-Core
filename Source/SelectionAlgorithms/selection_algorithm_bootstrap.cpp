#include "../API/galapagos.h"
#include "../galapagos_assemblies.h"

#include "tournament_selection.h"

GALAPAGOS_API void gc_bootstrap(gc_core* core) {
    stochastic* stochastic_instance = core->get_stochastic();

    core->register_selection_algorithm([stochastic_instance](selection_algorithm_metadata *metadata, selection_algorithm*& selection_algorithm) {
        auto *dynamic = dynamic_cast<tournament_selection_metadata *>(metadata);
        if (dynamic != nullptr) {
            selection_algorithm = new tournament_selection(stochastic_instance, dynamic);
            return true;
        }
        return false;
    });
}