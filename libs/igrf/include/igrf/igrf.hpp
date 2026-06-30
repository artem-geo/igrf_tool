#pragma once
#include <tuple>

namespace igrf {
    enum class LonEW {EAST, WEST};
    struct Coordinates {
        double lat;
        double lon;
        double hmsl;
        LonEW ew;
    };

    struct Date {
        int year;
        unsigned month;
        unsigned day;
    };

    struct Field {
        std::tuple<double, double, double> field;
        double inclination;
        double declination;
    };

    Field calc_igrf(const Coordinates& coords, const Date& date);
}
