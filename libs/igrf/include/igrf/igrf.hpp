#pragma once
#include "igrf/types.hpp"

namespace igrf {
    Field calc_igrf(const Coordinates& coords, const Date& date);
}
