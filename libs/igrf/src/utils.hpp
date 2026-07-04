#pragma once
#include "igrf/types.hpp"
#include <tuple>

namespace igrf::utils {
    using namespace igrf::types;

    double parse_date(const std::tuple<int, unsigned, unsigned>& date);
    std::tuple<double, double, double> parse_coords(const std::tuple<double, double, double>& coords);
    GH_vals get_coeffs(double date_decimal);
    int get_triangular(int n, int m);
    double calc_legendre(int n, int m, double colat_rad);
}
