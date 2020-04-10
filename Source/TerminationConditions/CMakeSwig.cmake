set_source_files_properties(termination_conditions.swg PROPERTIES CPLUSPLUS ON)

swig_add_library(termination_conditions_swig
        LANGUAGE
        python
        OUTPUT_DIR
        ${CMAKE_SOURCE_DIR}/bin  # was `bin/swig`
        OUTFILE_DIR
        ${CMAKE_SOURCE_DIR}/bin  # was `bin/swig/sources`
        SOURCES
        termination_conditions.swg
        fitness_threshold.cpp)

swig_link_libraries(termination_conditions_swig Python::Module Python::Python)