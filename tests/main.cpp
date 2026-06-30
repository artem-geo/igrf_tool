#include "igrf/igrf.hpp"
#include <iostream>

int main() 
{
    auto field = igrf::calc_igrf({34.0, 34.0, 100}, {2026, 1, 30});
    ////// debug coeff interpolation
    // auto min_max_epochs = igrf::utils::get_min_max_epochs(igrf::constants::COEFFS);
    // std::cout << min_max_epochs.first << ' ' << min_max_epochs.second << std::endl;
    return 0;
}