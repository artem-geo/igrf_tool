#include "coeffs.hpp"
#include "utils.hpp"
#include <chrono>
#include <cmath>
#include <stdexcept>

#include <iostream>

using namespace igrf::types;
using namespace igrf::constants;

namespace {
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
        double depoch = date_decimal - epoch_max;
        for (int i {0}; i < coeffs_max.g.size(); ++i) {
            coeffs_extr.g[i] = coeffs_max.g[i] + depoch * coeffs_sv.g[i];
            coeffs_extr.h[i] = coeffs_max.h[i] + depoch * coeffs_sv.h[i];
        }
    }

    void interpolate_coeffs(double date_decimal, GH_vals& coeffs)
    {
        int epoch_before {-1};
        int epoch_after {-1};
        for (const auto& [epoch, ecoeffs] : COEFFS) {
            if (epoch < date_decimal) {
                continue; // skip sv
            } else if (epoch == date_decimal) {
                coeffs.g = ecoeffs.g;
                coeffs.h = ecoeffs.h;
                return;
            } else {
                epoch_before = epoch - 5;
                epoch_after = epoch;
                break;
            }
        }
        const GH_vals& coeffs_before = COEFFS.at(epoch_before);
        const GH_vals& coeffs_after = COEFFS.at(epoch_after);
        double depoch = date_decimal - epoch_before;
        for (int i {0}; i < coeffs_before.g.size(); ++i) {
            coeffs.g[i] = coeffs_before.g[i] + depoch * 1/5 * (coeffs_after.g[i] - coeffs_before.g[i]);
            coeffs.h[i] = coeffs_before.h[i] + depoch * 1/5 * (coeffs_after.h[i] - coeffs_before.h[i]);
        }
    }

}

namespace igrf::utils {
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

    GH_vals get_coeffs(double date_decimal)
    {
        GH_vals coeffs;
        coeffs.g = std::vector<double>((COEFFS.begin()->second).g.size(), 0.0);
        coeffs.h = std::vector<double>((COEFFS.begin()->second).h.size(), 0.0);
        auto epoch_last = std::prev(COEFFS.end())->first;
        if (date_decimal > epoch_last)
            extrapolate_coeffs(date_decimal, coeffs);
        else
            interpolate_coeffs(date_decimal, coeffs);
        return coeffs;
    }
}