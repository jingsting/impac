#ifndef IMPAC_PACK_HPP
#define IMPAC_PACK_HPP

#include <vector>
#include "../rect.hpp"

namespace impac {
    // First-fit algorithm for packing a set of rectangles. Starts with the
    // largest rectangle (by area) and works top-to-bottom, left-to-right to
    // set each's rectangles position in `rects`. The total boundary size of
    // the positioned rectangles is returned in `total_w` and `total_h`.
    template<typename T, typename U>
    class simple_packer {
    public:
        simple_packer(
            std::vector<region<std::string, int>>&& regions,
            int max_width,
            int max_height);

        bool pack(int& total_width, int& total_height);

        const std::vector<region<std::string, int>>& regions const
        {
            return regions_;
        }
    private:
        std::vector<region<std::string, int>> regions_;
        int max_width_;
        int max_height_;
    };
}

#endif
