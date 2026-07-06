#pragma once 
#include <map>
#include <vector>

namespace igrf::constants {
    constexpr double a = 6'371.2; // igrf reference radius in km
    constexpr double Req_wgs84 = 6'378.137; // km
    constexpr double f_wgs84 = 1.0 / 298.257223563;
    constexpr double e2_wgs84 = f_wgs84 * (2.0 - f_wgs84);
}
namespace igrf::types {
    /// @brief Gauss coefficients; attribures g and h (both vectors of double)
    struct GH_vals {
        std::vector<double> g;
        std::vector<double> h;
    };
    using Coeffs = std::map<int, GH_vals>;

    /// @brief Magnetic Field; attribures = X, Y, and Z
    struct Field {
        double X {0.0};
        double Y {0.0};
        double Z {0.0};
    };
}