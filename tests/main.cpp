#include "igrf/igrf.hpp"
#include <iostream>
#include <cmath>

int main() 
{
    auto field = igrf::calc_igrf({50, -15, 4}, {2015, 6, 22});
    std::cout << "X component: " << field.X << std::endl;
    std::cout << "Y component: " << field.Y << std::endl;
    std::cout << "Z component: " << field.Z << std::endl;
    double T = std::sqrt(std::pow(field.X, 2) + std::pow(field.Y, 2) + std::pow(field.Z, 2));
    std::cout << "Total field: " << T << std::endl;
    ////// debug coeff interpolation
    // auto min_max_epochs = igrf::utils::get_min_max_epochs(igrf::constants::COEFFS);
    // std::cout << min_max_epochs.first << ' ' << min_max_epochs.second << std::endl;
    return 0;
}
