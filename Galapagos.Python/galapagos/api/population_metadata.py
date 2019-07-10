from galapagos.api import __galapagos_clib__

class PopulationMetadata:
    def __init__(self):
        self._handle = __galapagos_clib__.create_population_metadata()

        # size
        @property.getter
        def size() -> int:
            return __galapagos_clib__.get_population_metadata_size(self._handle)

        @property.setter
        def size(value: int) -> None:
            __galapagos_clib__.set_population_metadata_size(self._handle, value)

        # survival_rate
        @property.getter
        def survival_rate() -> int:
            return __galapagos_clib__.get_population_metadata_survival_rate(self._handle)

        @property.setter
        def survival_rate(value: int) -> None:
            __galapagos_clib__.set_population_metadata_survival_rate(self._handle, value)