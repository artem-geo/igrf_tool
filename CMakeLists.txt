cmake_minimum_required(VERSION 3.21)
project(igrf_tool
        VERSION 1.0.0
        DESCRIPTION "Small utility to calculate IGRF-14"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)

find_package(Python3 QUIET COMPONENTS Interpreter)
if(NOT Python3_Interpreter_FOUND)
    message(FATAL_ERROR
            "Python 3 is required to generate IGRF coefficients. "
            "Please install Python 3 and re-run CMake.")
endif()

set(IGRF_COEFFS_INPUT "${CMAKE_CURRENT_SOURCE_DIR}/python/igrf14coeffs.txt")
set(IGRF_COEFFS_PARSER "${CMAKE_CURRENT_SOURCE_DIR}/python/coeff_parser.py")
set(IGRF_COEFFS_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/libs/igrf/include/igrf/coeffs.hpp")

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

add_subdirectory(libs/igrf)
add_dependencies(igrf generate_igrf_coeffs)

add_executable(igrf_tool)
target_sources(igrf_tool
        PRIVATE main.cpp
)
target_link_libraries(igrf_tool PRIVATE igrf)
add_dependencies(igrf_tool generate_igrf_coeffs)
