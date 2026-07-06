#pragma once
#include "igrf/types.hpp"
#include <tuple>

namespace igrf::utils {
    using namespace igrf::types;

    double parse_date(const std::tuple<int, unsigned, unsigned>& date);
    std::tuple<double, double, double, double> parse_coords(const std::tuple<double, double, double>& coords);
}
