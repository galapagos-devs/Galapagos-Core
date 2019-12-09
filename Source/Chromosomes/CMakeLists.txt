# File names
set(CROSSOVERS_NAME Crossovers
        CACHE INTERNAL
        "Name of the lib built from the `Source/Crossovers` director")

set(MUTATIONS_NAME Mutations
        CACHE INTERNAL
        "Name of the lib built from the `Source/Mutations` directory")

# Add chromosome implementations
add_subdirectory(Vector)

if(BUILD_STATIC_LIBS)
    add_library(StaticChromosomes STATIC ${SRCS})

    target_link_libraries(StaticGalapagos
            $<TARGET_OBJECTS:StaticVectorChromosome>)

    set_target_properties(StaticGalapagos
            PROPERTIES
            OUTPUT_NAME ${SOURCE_NAME})
endif()