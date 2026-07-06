#include "coeffs.hpp"
#include "utils.hpp"
#include <chrono>
#include <cmath>
#include <stdexcept>

#include <iostream>

using namespace igrf::types;
using namespace igrf::constants;

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

    
}
