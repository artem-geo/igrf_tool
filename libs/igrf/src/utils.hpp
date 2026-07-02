#pragma once
#include "igrf/types.hpp"

namespace igrf::utils {
    constexpr double Re = 6'371'000; // earth radius in m
    double parse_date(const Date& date);
    CoordinatesIGRF parse_coords(const Coordinates& coords);
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
