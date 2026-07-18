#pragma once
#include "igrf/types.hpp"
#include <tuple>

namespace igrf {
    using namespace igrf::types;
    Field calc_igrf(const std::tuple<double, double, double>& coords,
        const std::tuple<int, unsigned, unsigned>& date);
    double get_total(const Field& field);
    double get_decl(const Field& field);
    double get_incl(const Field& field);
}
