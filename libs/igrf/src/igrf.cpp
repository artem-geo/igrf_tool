#include "igrf/igrf.hpp"
#include "coeffs.hpp"
#include "utils.hpp"

#include <cmath>
#include <format>
#include <iostream>

namespace igrf {
    using namespace igrf::utils;
    using namespace igrf::types;
    Field calc_igrf(const std::tuple<double, double, double>& coords, 
        const std::tuple<int, unsigned, unsigned>& date)
    {
        try {
            double decimal_date = parse_date(date);
            const auto& [colat, lon, alt] = parse_coords(coords);
            auto coeffs = get_coeffs(decimal_date);
            Field field;
            double cos_colat = std::cos(colat);
            double sin_colat = std::sin(colat);
            double radius_ratio;
            for (int n {1}; ; ++n) {
                radius_ratio = std::pow(constants::a / alt, n+2);
                for (int m {0}; m <= n; ++m) {
                    int idx = get_triangular(n, m);
                    const auto& g = coeffs.g.at(idx);
                    const auto& h = coeffs.h.at(idx);

                    // field.X += radius_ratio * (g*std::sin(m*lon) + h*std::cos(m*lon)) *
                    //     (n * cos_colat * calc_legendre(n, m, cos_colat) - (n+m)*calc_legendre(n-1, m, cos_colat))/sin_colat;
                    field.Y += radius_ratio * m/sin_colat * (g*std::sin(m*lon) - h*std::cos(m*lon)) * calc_legendre(n, m, cos_colat);
                    field.Z += (n+1) * radius_ratio * (g*std::sin(m*lon) + h*std::cos(m*lon)) * calc_legendre(n, m, cos_colat);

                    if (idx == coeffs.g.size()-1)
                        goto loop_break;
                }
            }

            loop_break:
            field.Z = -1 * field.Z;
            return field;
        } catch(std::exception& e) {
            throw std::runtime_error(std::format("Can't calculate IGRF: {}", e.what()));
        }
    }
}
