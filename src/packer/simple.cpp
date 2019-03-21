#include <algorithm>
#include <cassert>
#include "first_fit.hpp"

#include "simple_packer.hpp"

namespace impac {
    simple_packer::simple_packer(
        std::vector<region<std::string, int>>&& regions,
        int max_width,
        int max_height)
        : regions_{regions},
          max_width_{max_width},
          max_height_{max_height}
    {
        assert(max_width_ >= 0);
        assert(max_height_ >= 0);
    }

    bool simple_packer::pack(int& total_width, int& total_height)
    {
        // Sort regions by descending order of area.
        std::sort(
            regions_.begin(),
            regions_.end(),
            [](const auto& r1, const auto& r2) {
                return (
                    r1.area() > r2.area() ||
                    std::min(r1.width(), r1.height()) >
                    std::min(r2.width(), r2.height()));
            });

        auto i = unsigned{0};       // region index currently being placed
        auto region = regions_[i];  // region currently being placed

        // Scan through available space
        for (auto y = int{0}; y < max_height_; ++y) {
            // If vertical space isn't adequate, terminate loop.
            if (y + region.height() > max_height_)
                break;
            for (auto x = int{0}; x < max_width_; ++x) {
                // If horizontal space left isn't adequate, go to next row.
                if (x + region.width() > max_width_)
                    break;
                // Check if region intersects with any previously placed region.
                auto placed = true;
                region.set_position(x, y);
                for (auto j = unsigned{0}; j < i; ++j)
                    if (region.intersects(regions_[j]))
                        placed = false;
                if (placed) {
                    // Update the total width & total height consumed
                    total_width = std::max(total_width, region.right());
                    total_height = std::max(total_height, region.bottom());
                    // If all regions are placed, indicate success.
                    if (++i == regions_.size())
                        return true;
                    x += region.width();
                    region = regions_[i];
                }
            }
        }
        return false;
    }
}
