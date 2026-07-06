#include "igrf/igrf.hpp"
#include "coeffs.hpp"
#include "utils.hpp"

#include <algorithm>
#include <cmath>
#include <format>
#include <numbers>
#include <stdexcept>
#include <tuple>

using namespace igrf::types;
using namespace igrf::utils;
using namespace igrf::constants;

namespace {
    // tiny step when on poles
    constexpr double pole_epsilon = 1e-8;

    /// @brief Calculates Schmidt normalisation term
    /// @param n Spherical harmonic degree
    /// @param m Spherical harmonic order
    /// @return Schmidt normalisation term
    double schmidt_norm(int n, int m)
    {
        if (m == 0)
            return 1.0;
        // gamma function instead of factorials
        return std::sqrt(2.0 * std::exp(std::lgamma(n - m + 1.0) - std::lgamma(n + m + 1.0)));
    }

    /// @brief Calculates Schmidt quasi-normalized associated Legendre function 
    /// of degree n and order m
    /// @param n Spherical harmonic degree
    /// @param m Spherical harmonic order
    /// @param x Legendre function argument
    /// @return Schmidt quasi-normalized associated Legendre function value
    double legendre_schmidt(int n, int m, double x)
    {
        return schmidt_norm(n, m) * std::assoc_legendre(n, m, x);
    }

    /// @brief Calculates derivative of Schmidt quasi-normalized associated Legendre function 
    /// @param n Spherical harmonic degree (1,2,...)
    /// @param m Spherical harmonic order (0,1,...n)
    /// @param theta Geocentric colatitude (radians)
    /// @return Derivative value
    double dlegendre(int n, int m, double theta)
    {
        const double sin_theta = std::sin(theta);

        // pole handling
        if (std::abs(sin_theta) < pole_epsilon) {
            const double step = 1e-6;
            // clamp function forces theta to be inside the range
            const double theta_1 = std::clamp(theta - step, 0.0, std::numbers::pi);
            const double theta_2 = std::clamp(theta + step, 0.0, std::numbers::pi);

            if (theta_1 == theta_2)
                return 0.0;

            const double p1 = legendre_schmidt(n, m, std::cos(theta_1));
            const double p2 = legendre_schmidt(n, m, std::cos(theta_2));
            return (p2 - p1) / (theta_2 - theta_1); // returns finite difference
        }

        const double cos_theta = std::cos(theta);
        const double p_nm = legendre_schmidt(n, m, cos_theta);
        double p_prev = 0.0;

        if (m <= n - 1) { // only computes if legendre term exists
            p_prev = legendre_schmidt(n - 1, m, cos_theta);
            // rescaling of the previous term since derivative requires same scaling
            p_prev *= schmidt_norm(n, m) / schmidt_norm(n - 1, m);
        }

        return (n * cos_theta * p_nm - (n + m) * p_prev) / sin_theta;
    }

    /// @brief Calculates Schmidt quasi-normalized associated Legendre function devided by sin of colatitude.
    /// The term is used for the calculation of Y component
    /// @param n Spherical harmonic degree (1,2,...)
    /// @param m Spherical harmonic order (0,1,...n)
    /// @param theta Geocentric colatitude (radians)
    /// @return Schmidt quasi-normalized associated Legendre function value
    double legendre_over_sin(int n, int m, double theta)
    {
        if (m == 0)
            return 0.0;

        const double sin_theta = std::sin(theta);
        if (std::abs(sin_theta) >= pole_epsilon)
            return legendre_schmidt(n, m, std::cos(theta)) / sin_theta;

        const double theta_pole = theta < std::numbers::pi / 2 ? pole_epsilon : std::numbers::pi - pole_epsilon;
        return legendre_schmidt(n, m, std::cos(theta_pole)) / std::sin(theta_pole);
    }

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

namespace igrf {
    /// @brief Calculates IGRF for given WGS84 coordinates and date
    /// @param coords WGS84 coordinates (Latitude (dec deg), Longitude (dec deg), and Altitude (km AMSL))
    /// @param date Date to calculate IGRF (YYYY, MM, DD)
    /// @return Field object with field components as attributes (X, Y, Z; all geodetic)
    Field calc_igrf(const std::tuple<double, double, double>& coords,
        const std::tuple<int, unsigned, unsigned>& date)
    {
        try {
            const double decimal_date = parse_date(date);
            // theta = geocentric colatitude, phi = geocentric longitude
            // radius = geocentric radius, delta = lat_geod - lat_geoc
            const auto& [theta, phi, radius, delta] = parse_coords(coords);
            const auto coeffs = get_coeffs(decimal_date);

            Field field;
            for (int n = 1; ; ++n) {
                const double radius_ratio = std::pow(constants::a / radius, n + 2);

                for (int m = 0; m <= n; ++m) {
                    const int idx = get_triangular(n, m);
                    if (idx >= static_cast<int>(coeffs.g.size())) {
                        // geocentric -> geodetic
                        field.X = field.X * std::cos(delta) + field.Z * std::sin(delta);
                        field.Z = field.Z * std::cos(delta) - field.X * std::sin(delta);
                        return field;
                    }

                    const double& g = coeffs.g.at(idx);
                    const double& h = coeffs.h.at(idx);
                    const double cos_m_phi = std::cos(m * phi);
                    const double sin_m_phi = std::sin(m * phi);
                    const double gh = g * cos_m_phi + h * sin_m_phi;
                    const double p_nm = legendre_schmidt(n, m, std::cos(theta));
                    const double dp_nm = dlegendre(n, m, theta);

                    field.X += radius_ratio * gh * dp_nm;
                    field.Y += radius_ratio * m * (g * sin_m_phi - h * cos_m_phi)
                        * legendre_over_sin(n, m, theta);
                    field.Z -= (n + 1) * radius_ratio * gh * p_nm;
                }
            }
        } catch (const std::exception& e) {
            throw std::runtime_error(std::format("Can't calculate IGRF: {}", e.what()));
        }
    }
}
