project(igrf_lib)

#include(FetchContent)
#FetchContent_Declare(
#        eigen
#        GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
#        GIT_TAG d71c30c47858effcbd39967097a2d99ee48db464
#)
#FetchContent_MakeAvailable(eigen)

add_library(igrf STATIC)
target_sources(igrf PUBLIC
            src/igrf.cpp
            src/utils.cpp
        PUBLIC
            FILE_SET headers_public
            TYPE HEADERS
            BASE_DIRS include
            FILES
                include/igrf/igrf.hpp
                include/igrf/utils.hpp
                include/igrf/coeffs.hpp
)
#target_link_libraries(igrf PRIVATE eigen)