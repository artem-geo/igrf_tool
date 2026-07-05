#include "igrf/igrf.hpp"
#include "utils.hpp"

#include <algorithm>
#include <cmath>
#include <format>
#include <numbers>
#include <stdexcept>
#include <tuple>

namespace {
    constexpr double pole_epsilon = 1e-8;

    double schmidt_norm(int n, int m)
    {
        if (m == 0) {
            return 1.0;
        }

        return std::sqrt(2.0 * std::exp(std::lgamma(n - m + 1.0) - std::lgamma(n + m + 1.0)));
    }

    double legendre_schmidt(int n, int m, double cos_colat)
    {
        return schmidt_norm(n, m) * std::assoc_legendre(n, m, cos_colat);
    }

    double legendre_theta_derivative(int n, int m, double colat)
    {
        const double sin_colat = std::sin(colat);

        if (std::abs(sin_colat) < pole_epsilon) {
            const double step = 1e-6;
            const double theta_1 = std::clamp(colat - step, 0.0, std::numbers::pi);
            const double theta_2 = std::clamp(colat + step, 0.0, std::numbers::pi);

            if (theta_1 == theta_2) {
                return 0.0;
            }

            const double p1 = legendre_schmidt(n, m, std::cos(theta_1));
            const double p2 = legendre_schmidt(n, m, std::cos(theta_2));
            return (p2 - p1) / (theta_2 - theta_1);
        }

        const double cos_colat = std::cos(colat);
        const double p_nm = legendre_schmidt(n, m, cos_colat);
        double p_prev = 0.0;

        if (m <= n - 1) {
            p_prev = legendre_schmidt(n - 1, m, cos_colat);
            p_prev *= schmidt_norm(n, m) / schmidt_norm(n - 1, m);
        }

        return (n * cos_colat * p_nm - (n + m) * p_prev) / sin_colat;
    }

    double legendre_over_sin(int n, int m, double colat)
    {
        if (m == 0) {
            return 0.0;
        }

        const double sin_colat = std::sin(colat);
        if (std::abs(sin_colat) >= pole_epsilon) {
            return legendre_schmidt(n, m, std::cos(colat)) / sin_colat;
        }

        const double theta = colat < std::numbers::pi / 2 ? pole_epsilon : std::numbers::pi - pole_epsilon;
        return legendre_schmidt(n, m, std::cos(theta)) / std::sin(theta);
    }
}

namespace igrf {
    using namespace igrf::types;
    using namespace igrf::utils;

    Field calc_igrf2(const std::tuple<double, double, double>& coords,
        const std::tuple<int, unsigned, unsigned>& date)
    {
        try {
            const double decimal_date = parse_date(date);
            const auto& [colat, lon, radius] = parse_coords(coords);
            const auto coeffs = get_coeffs(decimal_date);

            Field field;
            for (int n = 1; ; ++n) {
                const double radius_ratio = std::pow(constants::a / radius, n + 2);

                for (int m = 0; m <= n; ++m) {
                    const int idx = get_triangular(n, m);
                    if (idx >= static_cast<int>(coeffs.g.size())) {
                        return field;
                    }

                    const double g = coeffs.g.at(idx);
                    const double h = coeffs.h.at(idx);
                    const double cos_m_lon = std::cos(m * lon);
                    const double sin_m_lon = std::sin(m * lon);
                    const double gh = g * cos_m_lon + h * sin_m_lon;
                    const double p_nm = legendre_schmidt(n, m, std::cos(colat));
                    const double dp_nm = legendre_theta_derivative(n, m, colat);

                    field.X += radius_ratio * gh * dp_nm;
                    field.Y += radius_ratio * m * (g * sin_m_lon - h * cos_m_lon)
                        * legendre_over_sin(n, m, colat);
                    field.Z -= (n + 1) * radius_ratio * gh * p_nm;
                }
            }
        } catch (const std::exception& e) {
            throw std::runtime_error(std::format("Can't calculate IGRF2: {}", e.what()));
        }
    }
}
