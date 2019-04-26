#include <algorithm>
#include <iostream>
#include "pack/first_fit_v2.hpp"

bool impac::pack::first_fit_v2(sprite_sheet& sprite_sheet)
{
    // ###########Using Ethan's code to sort sprites########################
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
    // #####################################################################
    size_t canvasw = sprite_sheet.width();
    size_t canvash = sprite_sheet.height();
    std::vector <std::vector<size_t> > canvas(canvash, std::vector<size_t>(canvasw, 0));
    for (auto i = size_t{0}; i < sprites.size(); ++i) {
        auto found = false;
        auto sprite = sprites[i];
        // auto max_x = sprite_sheet.width() - sprite->width();
        auto max_y = sprite_sheet.height() - sprite->height();
        
        for (auto h = size_t{0}; h <= max_y; ++h) {    
            auto wfits = 0;
            auto found = false;
            for (auto x = size_t{0}; x < sprite_sheet.width(); ++x) {
                auto lfits = true;
                for (auto y = h; y < (h+sprite->height()); ++y) {
                    if (canvas[x][y] != 0) {
                        lfits = false;
                        break;
                    }
                }
                if (lfits == true) {
                    wfits ++;
                } else {
                    wfits = 0;
                    continue;
                }
                if (wfits == sprite->width()) {
                    found = true;
                    auto startx = x+1-sprite->width();
                    auto starty = h;
                    sprite->set_position(startx, starty);
                    for (auto w = startx; w<startx+sprite->width(); ++w) {
                        for (auto h = starty; h<starty+sprite->height(); ++h) {
                            canvas[w][h] = 1;
                        }
                    }
                }
            }
        }
        if (found == false) {
            return false;
        }
    }
    return true;
}
