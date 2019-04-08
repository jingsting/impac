#include <algorithm>
#include <iostream>
#include "pack/first_fit.hpp"

bool impac::pack::first_fit(sprite_sheet& sprite_sheet)
{
    // Convert sprite map into a vector of sprites
    auto& sprites_map = sprite_sheet.sprites();
    auto sprites = std::vector<sprite*>(sprites_map.size());
    std::transform(
        sprites_map.begin(),
        sprites_map.end(),
        sprites.begin(),
        [](auto& p) { return &p.second; });
    // Sort sprites vector by descending order of area and then by descending
    // order of minimum dimension
    std::sort(
        sprites.begin(),
        sprites.end(),
        [](const auto& s1, const auto& s2) {
            return (
                s1->area() > s2->area() ||
                std::min(s1->width(), s1->height()) >
                std::min(s2->width(), s2->height()));
        });
    // Go through sprites in sequential order
    for (auto i = size_t{0}; i < sprites.size(); ++i) {
        // Blindly test every possible (x, y) position within the bounds of the
        // sprite sheet
        auto found_position = false;
        auto sprite = sprites[i];
        // If sprite sheet is too small to fit individual sprite then packing
        // fails.
        if (sprite_sheet.height() < sprite->height() ||
                sprite_sheet.width() < sprite->width()) {
            return false;
        }
        auto max_y = sprite_sheet.height() - sprite->height();
        auto max_x = sprite_sheet.width() - sprite->width();
        for (auto y = size_t{0}; y <= max_y; ++y) {
            for (auto x = size_t{0}; x <= max_x; ++x) {
                // Check if sprite intersects with any previously placed sprites
                // at this position
                sprite->set_position(x, y);
                bool intersects = false;
                for (auto j = size_t{0}; j < i; ++j) {
                    if (sprite->intersects(*sprites[j])) {
                        intersects = true;
                        break;
                    }
                }
                // If the sprite doesn't intersect, then we have successfully
                // placed it in its final position and we can break out of the
                // position search loop
                if (!intersects) {
                    found_position = true;
                    goto search_finished;
                }
            }
        }
search_finished:
        // No possible position for the sprite was found, packing failed
        if (!found_position)
            return false;
    }
    // All sprites were positioned without failure
    return true;
}
