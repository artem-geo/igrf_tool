#include "igrf/igrf.hpp"
#include "coeffs.hpp"
#include "utils.hpp"

#include <format>
#include <iostream>

namespace igrf {
    Field calc_igrf(const Coordinates& coords, const Date& date)
    {
        try {
            double decimal_date = utils::parse_date({date.year, date.month, date.day});
            std::cout << decimal_date << std::endl;
            // std::tuple<double, double, double> coords_igrf = parse_coords(coords);
            return Field();
        } catch(std::exception& e) {
            throw std::runtime_error(std::format("Can't calculate IGRF: {}", e.what()));
        }
    }
}
