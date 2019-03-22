#include <algorithm>
#include "first_fit.hpp"

bool impac::pack::first_fit(
    sprite_sheet& sprite_sheet,
    int& consumed_width,
    int& consumed_height)
{
    // Convert sprite map into a vector of sprites
    auto sprites = std::vector<sprite*>(sprite_sheet.sprites().size());
    std::transform(
        sprite_sheet.sprites().begin(),
        sprite_sheet.sprites().end(),
        sprites.begin(),
        [](auto& p) { return &p.second; });

    // Sort sprites vector by descending order of area
    std::sort(
        sprites.begin(),
        sprites.end(),
        [](auto s1, auto s2) {
            return (
                s1->area() > s2->area() ||
                std::min(s1->width(), s1->height()) >
                std::min(s2->width(), s2->height()));
        });

    auto i = unsigned{0};      // index of current sprite
    auto sprite = sprites[i];  // pointer to current sprite

    // Scan through the available area in left-to-right, top-to-bottom order
    for (auto y = int{0}; y < sprite_sheet.height(); ++y) {
        // If vertical space is exhausted, packing failed
        if (y + sprite->height() > sprite_sheet.height())
            break;
        for (auto x = int{0}; x < sprite_sheet.width(); ++x) {
            // If horizontal space is exhaused, move to next row
            if (x + sprite->width() > sprite_sheet.width())
                break;
            // Check if sprite intersects with any previously placed sprite at
            // this position
            sprite->set_position(x, y);
            auto intersects = false;
            for (auto j = unsigned{0}; j < i; ++j) {
                if (sprite->intersects(*sprites[j])) {
                    intersects = true;
                    break;
                }
            }
            if (!intersects) {
                // Update total width/height consumed
                consumed_width = std::max(consumed_width, sprite->right());
                consumed_height = std::max(consumed_height, sprite->bottom());
                // If all sprites are packed, return successfully
                if (++i == sprites.size())
                    return true;
                // Shift x by the consumed space and select next sprite
                x += sprite->width();
                sprite = sprites[i];
            }
        }
    }
    // Ran out of space, packing failed
    return false;
}
