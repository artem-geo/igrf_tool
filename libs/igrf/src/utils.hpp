#pragma once
#include <tuple>

namespace igrf::utils {
    double parse_date(const std::tuple<int, unsigned, unsigned>& date);
    std::tuple<double, double, double> parse_coords(const std::tuple<double, double, double, int>& coords);
    // std::pair<int, int> get_min_max_epochs(const Coeffs& coeffs);

    // enum class EpochType {
    //     EVEN,
    //     INTERIM,
    //     INVALID
    // };
    // EpochType get_epoch_type(double date);
    // void interp_coeffs(const Coeffs& coeffs, double date, GH_vals& epoch_res);
    // void get_igrf_coeffs(const Coeffs& coeffs, double date, GH_vals& epoch_res);

}

// namespace igrf {}
