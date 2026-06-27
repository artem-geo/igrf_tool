#include "../include/igrf/coeffs.hpp"
#include "../include/igrf/utils.hpp"
#include <limits>

namespace igrf::utils {
    std::pair<int, int> get_min_max_epochs(const Coeffs& coeffs) {
        std::pair<int, int> min_max_epochs {std::numeric_limits<int>::max(), std::numeric_limits<int>::min()};
        for (const auto& [epoch, coeff] : coeffs) {
            if (epoch >= 1900) {
                if (min_max_epochs.first > epoch) {
                    min_max_epochs.first = epoch;
                } else if (min_max_epochs.second < epoch)
                    min_max_epochs.second = epoch;
            }
        }
        return min_max_epochs;
    }
    double to_decimal_year(const std::chrono::year_month_day& date) {
        if (!date.ok())
            throw std::ios_base::failure("Wrong date format");
        auto year = date.year();
        int ndays = year.is_leap() ? 366 : 365;
        std::chrono::sys_days start = std::chrono::sys_days {year / std::chrono::January / 1};
        std::chrono::sys_days current = std::chrono::sys_days(date);
        int days_passed = (current - start).count();
        return int(year) + static_cast<double>(days_passed) / ndays;
    }

    EpochType get_epoch_type(double date) {
        if (date < 1900.000 || date >= 2030.000)
            return EpochType::INVALID;
        else if ((date - static_cast<int>(date)) < 0.001)
            return EpochType::EVEN;
        else
            return EpochType::INTERIM;
    }

    void interp_coeffs(const Coeffs& coeffs, double date, GH_vals& epoch_res) {
        int date_pre = static_cast<int>(date);
        auto [epoch_min, epoch_max] = get_min_max_epochs(coeffs);

        const GH_vals& epoch_pre = coeffs.at(date_pre);

        if (date < epoch_max) {
            const GH_vals& epoch_post = coeffs.at(date_pre + 5);
            for (int i {0}; i < epoch_pre.g.size(); ++i) {
                epoch_res.g[i] = epoch_pre.g[i] + (date - date_pre) * 1/5 * (epoch_post.g[i] - epoch_post.g[i]);
                epoch_res.h[i] = epoch_pre.h[i] + (date - date_pre) * 1/5 * (epoch_post.h[i] - epoch_post.h[i]);
            }
        } else {
            const GH_vals& epoch_sv = coeffs.at(0);
            for (int i {0}; i < epoch_pre.g.size(); ++i) {
                epoch_res.g[i] = epoch_pre.g[i] + (date - date_pre) * epoch_sv.g[i];
                epoch_res.h[i] = epoch_pre.h[i] + (date - date_pre) * epoch_sv.h[i];
            }
        }
    }

    void get_igrf_coeffs(const Coeffs& coeffs, double date, GH_vals& epoch_res) {
        EpochType epoch_type = get_epoch_type(date);
        switch (epoch_type) {
        case EpochType::INVALID:
            throw std::ios_base::failure("Wrong input date (should be >1900/01/01 and < 2030/12/31");
        case EpochType::EVEN:
            epoch_res = coeffs.at(static_cast<int>(date));
            break;
        case EpochType::INTERIM:
            interp_coeffs(coeffs, date, epoch_res);
        }
    }
}
