#pragma once
#include "igrf/types.hpp"
#include <tuple>

namespace igrf::utils {
    using namespace igrf::types;

    double parse_date(const std::tuple<int, unsigned, unsigned>& date);
    std::tuple<double, double, double> parse_coords(const std::tuple<double, double, double>& coords);
    std::pair<int, int> get_min_max_epochs(const Coeffs& coeffs);
    void extrapolate_coeffs(const Coeffs& coeffs_all, int max_epoch, GH_vals& coeffs_extr);
    GH_vals get_coeffs(double date_decimal);
    

}
