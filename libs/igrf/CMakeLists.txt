add_library(igrf STATIC)
target_sources(igrf
        PRIVATE
            src/igrf.cpp
            src/utils.cpp
        PUBLIC
            FILE_SET headers_public
            TYPE HEADERS
            BASE_DIRS include
            FILES
                include/igrf/igrf.hpp
        PRIVATE
            FILE_SET headers_private
            TYPE HEADERS
            BASE_DIRS src
            FILES
                src/utils.hpp
                src/coeffs.hpp
)

find_package(Python3 QUIET COMPONENTS Interpreter)
if(NOT Python3_Interpreter_FOUND)
    message(FATAL_ERROR
            "Python 3 is required to generate IGRF coefficients. "
            "Please install Python 3 and re-run CMake.")
endif()

set(IGRF_COEFFS_INPUT "${CMAKE_CURRENT_SOURCE_DIR}/../../python/igrf14coeffs.txt")
set(IGRF_COEFFS_PARSER "${CMAKE_CURRENT_SOURCE_DIR}/../../python/coeff_parser.py")
set(IGRF_COEFFS_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/src/coeffs.hpp")

add_custom_target(generate_igrf_coeffs ALL
        COMMAND Python3::Interpreter
                "${IGRF_COEFFS_PARSER}"
                "${IGRF_COEFFS_INPUT}"
                "${IGRF_COEFFS_HEADER}"
        BYPRODUCTS "${IGRF_COEFFS_HEADER}"
        DEPENDS
                "${IGRF_COEFFS_PARSER}"
                "${IGRF_COEFFS_INPUT}"
        COMMENT "Generating IGRF coefficient header"
        VERBATIM
)

if(TARGET generate_igrf_coeffs)
    add_dependencies(igrf generate_igrf_coeffs)
endif()
