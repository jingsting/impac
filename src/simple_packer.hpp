#ifndef IMPAC_SIMPLE_PACKER_HPP
#define IMPAC_SIMPLE_PACKER_HPP

#include <string>
#include <vector>
#include "region.hpp"

namespace impac {
    // Uses the first-fit algorithm to pack a set of regions. Starts with the
    // largest region (by area) and works left-to-right, top-to-bottom to
    // position its rectangles.
    class simple_packer {
    public:
        using region_type = region<std::string, int>;

        // Constructs a packer with a vector of regions, an available width,
        // and an available height
        simple_packer(
            std::vector<region_type>&& regions,
            int available_width,
            int available_height);

        // Packs regions into our available width/height and and assign the
        // total width/height consumed. Returns a boolean value indicating
        // whether or not packing was success.
        bool pack(int& total_width, int& total_height);

        // Gets a reference to the regions
        const std::vector<region_type>& regions() const { return regions_; }

        // Gets the available width
        int available_width() const { return available_width_; }

        // Gets the available height
        int available_height() const { return available_height_; }
    private:
        // Regions that are positioned by pack(..)
        std::vector<region<std::string, int>> regions_;

        int available_width_;   // width available to the packing algorithm
        int available_height_;  // height available to the packing algorithm
    };
}

#endif
