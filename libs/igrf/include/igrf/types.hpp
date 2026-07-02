#pragma once 
#include <map>
#include <vector>

namespace igrf::types {
    constexpr double Re = 6'371; // earth radius in km
    struct GH_vals {
        std::vector<double> g;
        std::vector<double> h;
    };
    using Coeffs = std::map<int, GH_vals>;

    struct Field {
        double Bx;
        double By;
        double Bz;
        double B;
        double inclination;
        double declination;
    };
}