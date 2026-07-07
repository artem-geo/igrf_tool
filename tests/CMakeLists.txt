include(FetchContent)

FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.5.2
)
FetchContent_MakeAvailable(doctest)

add_executable(igrf_test
    test_main.cpp
    test_igrf.cpp
)
target_link_libraries(igrf_test
    PRIVATE
        igrf
        doctest::doctest
)

add_test(
    NAME igrf_test
    COMMAND igrf_test
)