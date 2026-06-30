#pragma once
#include <tuple>

namespace igrf {
    struct Field {
        std::tuple<double, double, double> field;
        double inclination;
        double declination;
    };
    Field calc_igrf(const std::tuple<double, double, double>& coords, 
        const std::tuple<int, unsigned, unsigned>& date);
}