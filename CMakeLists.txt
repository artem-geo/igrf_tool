cmake_minimum_required(VERSION 3.21)
project(igrf_tool
        VERSION 1.0.0
        DESCRIPTION "Small library + optional GUI to calculate IGRF-14"
        LANGUAGES CXX
)
include(CTest)
set(CMAKE_CXX_STANDARD 23)
option(IGRF_BUILD_GUI "Build the wxWidgets GUI application" OFF)

add_subdirectory(libs/igrf)

if(IGRF_BUILD_GUI)
        add_subdirectory(gui)
endif()

if(BUILD_TESTING)
        add_subdirectory(tests)
endif()
