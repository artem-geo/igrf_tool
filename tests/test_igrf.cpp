#include <doctest/doctest.h>

#include "igrf/igrf.hpp"

#include <cmath>
#include <stdexcept>

namespace {
    void check_field(const igrf::types::Field& field,
        double expected_x,
        double expected_y,
        double expected_z)
    {
        CHECK(std::abs(field.X - expected_x) < 1.0);
        CHECK(std::abs(field.Y - expected_y) < 1.0);
        CHECK(std::abs(field.Z - expected_z) < 1.0);
    }
}

TEST_CASE("calc_igrf returns field value at the northern pole at MSL on 2022/02/24")
{
    igrf::types::Field field = igrf::calc_igrf({90.0, 0.0, 0.0}, {2022, 2, 24});

    check_field(field, 1780, 0, 56781);
}

TEST_CASE("calc_igrf returns field value over London at 1 km AMSL on 2025/01/01")
{
    igrf::types::Field field = igrf::calc_igrf({51.5, -0.1, 1.0}, {2025, 1, 1});

    check_field(field, 19539, 309, 44980);
}

TEST_CASE("calc_igrf returns field value over Sydney at 5 km AMSL on 2025/01/01")
{
    igrf::types::Field field = igrf::calc_igrf({-33.9, 151.2, 5.0}, {2025, 1, 1});

    check_field(field, 23956, 5434, -51288);
}

TEST_CASE("calc_igrf rejects coordinates outside supported ranges")
{
    CHECK_THROWS_AS(igrf::calc_igrf({90.1, 0.0, 0.0}, {2025, 1, 1}), std::runtime_error);
    CHECK_THROWS_AS(igrf::calc_igrf({0.0, -180.1, 0.0}, {2025, 1, 1}), std::runtime_error);
    CHECK_THROWS_AS(igrf::calc_igrf({0.0, 0.0, -2300.1}, {2025, 1, 1}), std::runtime_error);
}

TEST_CASE("calc_igrf rejects dates outside supported ranges")
{
    CHECK_THROWS_AS(igrf::calc_igrf({0.0, 0.0, 0.0}, {1899, 1, 1}), std::runtime_error);
    CHECK_THROWS_AS(igrf::calc_igrf({0.0, 0.0, 0.0}, {2031, 1, 1}), std::runtime_error);
    CHECK_THROWS_AS(igrf::calc_igrf({0.0, 0.0, 0.0}, {2025, 2, 29}), std::runtime_error);
}
