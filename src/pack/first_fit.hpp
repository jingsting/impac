#ifndef IMPAC_PACK_FIRST_FIT_HPP
#define IMPAC_PACK_FIRST_FIT_HPP

#include "sprite_sheet.hpp"

namespace impac {
    namespace pack {
        // Positions the sprites on a sprite sheet based on a simple first-fit
        // algorithm. The algorithm works by sorting the sprites by descending
        // order of area and then attempting to pack them left-to-right,
        // top-to-bottom until all sprites are placed. The amount of width and
        // height actually consumed by the final sprites is returned in
        // `consumed_width` and `consumed_height`. Returns true for success and
        // false if there wasn't enough space in the sprite sheet.
        bool first_fit(
            sprite_sheet& sprite_sheet,
            int& consumed_width,
            int& consumed_height);
    }
}

#endif // IMPAC_PACK_FIRST_FIT_HPP
