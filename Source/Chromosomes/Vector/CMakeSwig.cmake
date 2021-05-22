set_source_files_properties(vector_chromosome.swg PROPERTIES CPLUSPLUS ON)

swig_add_library(vector_chromosome_swig
        LANGUAGE
        python
        OUTPUT_DIR
        ${CMAKE_SOURCE_DIR}/bin  # was `bin/swig`
        OUTFILE_DIR
        ${CMAKE_SOURCE_DIR}/bin  # was `bin/swig/sources`
        SOURCES
        vector_chromosome.swg
        vector_chromosome.cpp
        kpoint_crossover.cpp
        gaussian_mutation.cpp
        randomization_mutation.cpp)

swig_link_libraries(vector_chromosome_swig Python::Module Python::Python)