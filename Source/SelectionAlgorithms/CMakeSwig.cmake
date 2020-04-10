set_source_files_properties(selection_algorithms.swg PROPERTIES CPLUSPLUS ON)

swig_add_library(selection_algorithms_swig
        LANGUAGE
        python
        OUTPUT_DIR
        ${CMAKE_SOURCE_DIR}/bin  # was `bin/swig`
        OUTFILE_DIR
        ${CMAKE_SOURCE_DIR}/bin  # was `bin/swig/sources`
        SOURCES
        selection_algorithms.swg
        tournament_selection.cpp)

swig_link_libraries(selection_algorithms_swig Python::Module Python::Python)