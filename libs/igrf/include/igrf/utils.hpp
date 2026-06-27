#pragma once
#include "coeffs.hpp"
#include <chrono>

namespace igrf::utils {
    std::pair<int, int> get_min_max_epochs(const Coeffs& coeffs);
    double to_decimal_year(const std::chrono::year_month_day& date);

    enum class EpochType {
        EVEN,
        INTERIM,
        INVALID
    };
    EpochType get_epoch_type(double date);
    void interp_coeffs(const Coeffs& coeffs, double date, GH_vals& epoch_res);
    void get_igrf_coeffs(const Coeffs& coeffs, double date, GH_vals& epoch_res);

}

namespace igrf {}
