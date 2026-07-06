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
        if (m == 0)
            return 1.0;
        return std::sqrt(2.0 * std::exp(std::lgamma(n - m + 1.0) - std::lgamma(n + m + 1.0)));
    }

    double legendre_schmidt(int n, int m, double x)
    {
        return schmidt_norm(n, m) * std::assoc_legendre(n, m, x);
    }

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
}

namespace igrf {
    using namespace igrf::types;
    using namespace igrf::utils;

    Field calc_igrf(const std::tuple<double, double, double>& coords,
        const std::tuple<int, unsigned, unsigned>& date)
    {
        try {
            const double decimal_date = parse_date(date);
            // theta = geocentric colatitude, phi = geocentric longitude
            // radius = geocentric radius
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
