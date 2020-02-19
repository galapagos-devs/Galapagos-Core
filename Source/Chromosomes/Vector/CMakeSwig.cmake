set_source_files_properties(vector_chromosome.swg PROPERTIES CPLUSPLUS ON)

swig_add_library(vector_chromosome_swig
        LANGUAGE
        python
        OUTPUT_DIR
        ${CMAKE_SOURCE_DIR}/bin/swig
        OUTFILE_DIR
        ${CMAKE_SOURCE_DIR}/bin/swig/sources
        SOURCES
        vector_chromosome.swg
        vector_chromosome.cpp)

swig_link_libraries(vector_chromosome_swig Python::Module Python::Python)