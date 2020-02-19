set_source_files_properties(galapagos.swg PROPERTIES CPLUSPLUS ON)

swig_add_library(galapagos_swig
        LANGUAGE python
        OUTPUT_DIR ${CMAKE_SOURCE_DIR}/bin/swig
        OUTFILE_DIR ${CMAKE_SOURCE_DIR}/bin/swig/sources
        SOURCES
            galapagos.swg
            galapagos.cpp
            stochastic_internal.cpp
            genetic_factory.cpp
            population_internal.cpp
            creature_internal.cpp)

swig_link_libraries(galapagos_swig Python::Module Python::Python)