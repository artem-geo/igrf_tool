#include "igrf/igrf.hpp"
#include "coeffs.hpp"
#include "utils.hpp"

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
            auto coords_igrf = parse_coords(coords);
            auto coeffs = get_coeffs(decimal_date);
            
            return Field();
        } catch(std::exception& e) {
            throw std::runtime_error(std::format("Can't calculate IGRF: {}", e.what()));
        }
    }
}
