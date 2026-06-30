#include "igrf/igrf.hpp"
#include "coeffs.hpp"
#include "utils.hpp"

#include <format>
#include <iostream>

namespace igrf {
    Field calc_igrf(const std::tuple<double, double, double>& coords,
        const std::tuple<int, unsigned, unsigned>& date)
    {
        try {
            double decimal_date = utils::parse_date(date);
            std::cout << decimal_date << std::endl;
            // std::tuple<double, double, double> coords_igrf = parse_coords(coords);
            return Field();
        } catch(std::exception& e) {
            throw std::runtime_error(std::format("Can't get IGRF: {}", e.what()));
        }
    }
}