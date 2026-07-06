#include "coeffs.hpp"
#include "utils.hpp"
#include <chrono>
#include <cmath>
#include <stdexcept>

#include <iostream>

using namespace igrf::types;
using namespace igrf::constants;

namespace {
    /// @brief Extrapolates Gauss coefficients when date greater than the final epoch
    /// @param date_decimal Decimal date
    /// @param coeffs_extr Extrapolated coefficients
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

    /// @brief Interpolates Gauss coefficients between two epochs
    /// @param date_decimal Decimal date
    /// @param coeffs All Gauss coefficients
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
    /// @brief Valudates and transforms provided date
    /// @param date Date (YYYY, MM, DD)
    /// @return Decimal year 
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

    /// @brief Validates and transforms provided coordinates
    /// @param coords WGS84 geodetic coordinates (Latitude (dec deg), Longitude (dec deg), Altitude (km AMSL))
    /// @return Geocentric coordinates (Colatitude (rad), Longitude(rad), Radial distance (km), 
    /// Delta (Latitude Geodetic - Latitude Geocentric (rad)))
    std::tuple<double, double, double, double> parse_coords(const std::tuple<double, double, double>& coords)
    {
        const auto& [lat_geod_deg, lon_geod_deg, alt_geod] = coords;
        if (lat_geod_deg < -90 || lat_geod_deg > 90.0)
            throw std::runtime_error("Invalid latitude. Valid range [-90.0, 90.0]");
        if (lon_geod_deg < -180|| lon_geod_deg > 180)
            throw std::runtime_error("Invalid longitude. Valid range[-180, 180]");
        if (alt_geod < -2'300)
            throw std::runtime_error("Altitude should be > -2'300'000 m");

        const double lat_geod = lat_geod_deg * M_PI / 180;
        const double sin_lat = std::sin(lat_geod);
        const double cos_lat = std::cos(lat_geod);
        
        // N = prime vertical radius of curvature
        const double N = Req_wgs84 / std::sqrt(1.0 - e2_wgs84 * sin_lat * sin_lat);

        const double rho = (N + alt_geod) * cos_lat;
        const double z = (N * (1.0 - e2_wgs84) + alt_geod) * sin_lat;
        const double lat_geoc = std::atan2(z, rho);
        const double radius = std::hypot(rho, z);
        const double colat_geoc = M_PI / 2 - lat_geoc;
        const double lon_geoc = ((lon_geod_deg >= 0) ? lon_geod_deg : 360 + lon_geod_deg) * M_PI / 180;

        const double delta = lat_geod - lat_geoc;

        return {colat_geoc, lon_geoc, radius, delta};
    }

    /// @brief Extracts Gauss coefficient corresponding to a certain date
    /// @param date_decimal Decimal date
    /// @return Gauss coefficient for date_decimal
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

    /// @brief Calculates a triangular value
    /// @param n Spherical harmonic degree
    /// @param m Spherical harmonic order
    /// @return Resultant triangular value
    int get_triangular(int n, int m)
    {
        return n*(n+1)/2 - 1 + m;
    }
}
