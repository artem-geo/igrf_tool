#pragma once 

namespace igrf {
    enum class LonEW {EAST, WEST};
    enum class LatNS {NORTH, SOUTH};
    struct Coordinates {
        double lat;
        LatNS ns;
        double lon;
        LonEW ew;
        double alt;
    };
    struct CoordinatesIGRF {
        double colat;
        double lon;
        double r;
    };
    struct Date {
        int year;
        unsigned month;
        unsigned day;
    };

    struct Field {
        double Bx;
        double By;
        double Bz;
        double B;
        double inclination;
        double declination;
    };
}