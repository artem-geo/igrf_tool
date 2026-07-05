#pragma once
#include "igrf/types.hpp"
#include <tuple>

namespace igrf {
    using namespace igrf::types;
    Field calc_igrf(const std::tuple<double, double, double>& coords, 
        const std::tuple<int, unsigned, unsigned>& date);
    Field calc_igrf2(const std::tuple<double, double, double>& coords,
        const std::tuple<int, unsigned, unsigned>& date);
}
