#include "coeffs.hpp"
#include "utils.hpp"
#include <chrono>
#include <cmath>
#include <stdexcept>

#include <iostream>

namespace igrf::utils {
    using namespace igrf::types;
    using namespace igrf::constants;

    double parse_date(const std::tuple<int, unsigned, unsigned>& date)
    {
        auto epoch_max = std::prev(COEFFS.end())->first + 5;
        const auto& [y, m, d] = date;
        if (y < 1900 || y > epoch_max)
            throw std::runtime_error(std::format("Year can't be < 1900 and >{}", epoch_max));
        std::chrono::year year{y};
        std::chrono::year_month_day ymd {year, std::chrono::month{m}, std::chrono::day{d}};
        if (!ymd.ok())
            throw std::runtime_error("Wrong date");
        auto tp = std::chrono::sys_days(ymd);

        // ymd beginning of year
        std::chrono::year_month_day ymd_boy {year, std::chrono::month{1}, std::chrono::day{1}};
        auto tp_boy = std::chrono::sys_days(ymd_boy);

        auto dtp = tp - tp_boy;
        auto ndays_year = year.is_leap() ? 366 : 365;

        return y + static_cast<double>(dtp.count()) / ndays_year;
    }

    std::tuple<double, double, double> parse_coords(const std::tuple<double, double, double>& coords)
    {
        const auto& [lat, lon, alt] = coords;
        if (lat < -90 || lat > 90.0)
            throw std::runtime_error("Invalid latitude. Valid range [-90.0, 90.0]");
        if (lon < -180|| lon > 180)
            throw std::runtime_error("Invalid longitude. Valid range[-180, 180]");
        if (alt < -2'300)
            throw std::runtime_error("Altitude should be > -2'300'000 m");
        double colat = 90 - lat;
        double lon_new = (lon > 0) ? lon : 360 + lon;
        double alt_new = Re + alt;
        
        colat = colat * M_PI / 180;
        lon_new = lon_new * M_PI / 180;

        return {colat, lon_new, alt_new};
    }

    int get_triangular(int n, int m)
    {
        return n*(n+1)/2 - 1 + m;
    }

    void extrapolate_coeffs(double date_decimal, GH_vals& coeffs_extr)
    {
        const GH_vals& coeffs_max = std::prev(COEFFS.end())->second;
        double epoch_max = std::prev(COEFFS.end())->first;
        const GH_vals& coeffs_sv = COEFFS.at(0);
        coeffs_extr.g = std::vector<double>(coeffs_max.g.size(), 0.0);
        coeffs_extr.h = std::vector<double>(coeffs_max.h.size(), 0.0);
        for (int i {0}; i < coeffs_max.g.size(); ++i) {
            coeffs_extr.g[i] = coeffs_max.g[i] + (date_decimal - epoch_max) * coeffs_sv.g[i];
            coeffs_extr.h[i] = coeffs_max.h[i] + (date_decimal - epoch_max) * coeffs_sv.h[i];
        }
    }

    GH_vals get_coeffs(double date_decimal)
    {
        GH_vals coeffs;
        coeffs.g = std::vector<double>((COEFFS.begin()->second).g.size(), 0.0);
        coeffs.h = std::vector<double>((COEFFS.begin()->second).h.size(), 0.0);
        auto epoch_last = std::prev(COEFFS.end())->first;
        if (date_decimal > epoch_last)
            extrapolate_coeffs(date_decimal, coeffs);
        // else
        //     interpolate_coeffs(igrf::constants::COEFFS, coeffs);


        return coeffs;
    }
}

// namespace igrf::utils {



    // double to_decimal_year(const std::chrono::year_month_day& date)
    // {
    //     if (!date.ok())
    //         throw std::ios_base::failure("Wrong date format");
    //     auto year = date.year();
    //     int ndays = year.is_leap() ? 366 : 365;
    //     std::chrono::sys_days start = std::chrono::sys_days {year / std::chrono::January / 1};
    //     std::chrono::sys_days current = std::chrono::sys_days(date);
    //     int days_passed = (current - start).count();
    //     return int(year) + static_cast<double>(days_passed) / ndays;
    // }

//     EpochType get_epoch_type(double date) {
//         if (date < 1900.000 || date >= 2030.000)
//             return EpochType::INVALID;
//         else if ((date - static_cast<int>(date)) < 0.001)
//             return EpochType::EVEN;
//         else
//             return EpochType::INTERIM;
//     }

//     void interp_coeffs(const Coeffs& coeffs, double date, GH_vals& epoch_res) {
//         int date_pre = static_cast<int>(date);
//         auto [epoch_min, epoch_max] = get_min_max_epochs(coeffs);

//         const GH_vals& epoch_pre = coeffs.at(date_pre);

//         if (date < epoch_max) {
//             const GH_vals& epoch_post = coeffs.at(date_pre + 5);
//             for (int i {0}; i < epoch_pre.g.size(); ++i) {
//                 epoch_res.g[i] = epoch_pre.g[i] + (date - date_pre) * 1/5 * (epoch_post.g[i] - epoch_post.g[i]);
//                 epoch_res.h[i] = epoch_pre.h[i] + (date - date_pre) * 1/5 * (epoch_post.h[i] - epoch_post.h[i]);
//             }
//         } else {
//             const GH_vals& epoch_sv = coeffs.at(0);
//             for (int i {0}; i < epoch_pre.g.size(); ++i) {
//                 epoch_res.g[i] = epoch_pre.g[i] + (date - date_pre) * epoch_sv.g[i];
//                 epoch_res.h[i] = epoch_pre.h[i] + (date - date_pre) * epoch_sv.h[i];
//             }
//         }
//     }

//     void get_igrf_coeffs(const Coeffs& coeffs, double date, GH_vals& epoch_res) {
//         EpochType epoch_type = get_epoch_type(date);
//         switch (epoch_type) {
//         case EpochType::INVALID:
//             throw std::ios_base::failure("Wrong input date (should be >1900/01/01 and < 2030/12/31");
//         case EpochType::EVEN:
//             epoch_res = coeffs.at(static_cast<int>(date));
//             break;
//         case EpochType::INTERIM:
//             interp_coeffs(coeffs, date, epoch_res);
//         }
//     }
// }
