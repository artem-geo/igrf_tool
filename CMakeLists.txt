cmake_minimum_required(VERSION 3.21)
project(igrf_tool
        VERSION 1.0.0
        DESCRIPTION "Small utility to calculate IGRF-14"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(libs/igrf)
add_subdirectory(tests)

# add_subdirectory(gui)
# add_dependencies(igrf_tool generate_igrf_coeffs)


# add_executable(igrf_tool)
# target_sources(igrf_tool
#         PRIVATE main.cpp
# )
# target_link_libraries(igrf_tool PRIVATE igrf)
# add_dependencies(igrf_tool generate_igrf_coeffs)
