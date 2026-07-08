# IGRF Tool

IGRF Tool is a tiny C++23 project for calculating magnetic field components
with the IGRF-14 model.

The project currently provides a static C++ library and tests. An optional GUI will be implemented soon.

## Features

- Calculates geodetic magnetic field components `X`, `Y`, and `Z`.
- Uses WGS84 geodetic coordinates.
- Supports dates from 1900 through the final supported IGRF-14 extrapolation
  range.
- Generates C++ coefficient data from the bundled IGRF-14 coefficient file.
- Includes doctest-based tests for known locations and input validation.

## Requirements

- CMake 3.21 or newer
- A C++23 compiler
- Ninja, when using the provided CMake presets
- Python 3, used during the build to generate the coefficient header

Tests use doctest through CMake `FetchContent`, so configuring the test build
requires network access unless doctest is already available in CMake's download
cache.

## Build

Configure and build the debug preset:

```sh
cmake --preset debug
cmake --build --preset debug
```

Build the release preset:

```sh
cmake --preset release
cmake --build --preset release
```

## Test

```sh
ctest --preset debug
```

## Usage

The public API is declared in `libs/igrf/include/igrf/igrf.hpp`.

```cpp
#include <igrf/igrf.hpp>

int main()
{
    // Coordinates: latitude in decimal degrees, longitude in decimal degrees,
    // altitude in kilometers above mean sea level.
    const auto coords = std::tuple{51.5, -0.1, 1.0};

    // Date: year, month, day.
    const auto date = std::tuple{2025, 1u, 1u};

    const igrf::types::Field field = igrf::calc_igrf(coords, date);

    // field.X, field.Y, and field.Z contain the geodetic field components.
}
```

Input ranges are validated:

- Latitude: `[-90.0, 90.0]` degrees
- Longitude: `[-180.0, 180.0]` degrees
- Altitude: greater than `-2300` km

Invalid inputs throw `std::runtime_error`.

## Project Layout

```text
libs/igrf/   C++ library implementation and public headers
python/      IGRF-14 coefficient data and coefficient parser
tests/       doctest test suite
gui/         GUI placeholder; full GUI implementation coming soon
```
