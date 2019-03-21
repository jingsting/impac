#ifndef IMPAC_PACK_HPP
#define IMPAC_PACK_HPP

#include <string>
#include <vector>
#include "region.hpp"

namespace impac {
    // First-fit algorithm for packing a set of rectangles. Starts with the
    // largest rectangle (by area) and works top-to-bottom, left-to-right to
    // set each's rectangles position in `rects`. The total boundary size of
    // the positioned rectangles is returned in `total_w` and `total_h`.
    class simple_packer {
    public:
        using region_type = region<std::string, int>;

        simple_packer(
            std::vector<region_type>&& regions,
            int max_width,
            int max_height);

        bool pack(int& total_width, int& total_height);

        const std::vector<region_type>& regions() const { return regions_; }
        int max_width() const { return max_width_; }
        int max_height() const { return max_height_; }
    private:
        std::vector<region<std::string, int>> regions_;
        int max_width_;
        int max_height_;
    };
}

#endif
