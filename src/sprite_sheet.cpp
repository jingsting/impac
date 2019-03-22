#include <cassert>
#include <algorithm>
#include "sprite_sheet.hpp"

namespace impac {
    sprite_sheet::sprite_sheet(int width, int height)
        : sprites_{}, width_{width}, height_{height}
    {
        check_rep();
    }

    sprite_sheet::sprite_sheet(sprites_type&& sprites, int width, int height)
        : sprites_{sprites}, width_{width}, height_{height}
    {
        check_rep();
    }

    sprite_sheet::sprite_sheet(
        const std::unordered_map<std::string, image_type>& images,
        int width,
        int height)
        : sprites_{images.size()},
          width_{width},
          height_{height}
    {
        for (const auto& [tag, image] : images)
            add_sprite(tag, image);
        check_rep();
    }

    bool sprite_sheet::add_sprite(const std::string& tag, sprite&& sprite)
    {
        return sprites_.emplace(tag, sprite).second;
    }

    bool sprite_sheet::add_sprite(
        const std::string& tag,
        const image_type& image)
    {
        return add_sprite(tag, sprite{image});
    }

    sprite_sheet::sprites_type& sprite_sheet::sprites()
    {
        return sprites_;
    }

    int sprite_sheet::width() const { return width_; }

    int sprite_sheet::height() const { return height_; }

    void sprite_sheet::check_rep() const
    {
        assert(width_ >= 0);
        assert(height_ >= 0);
    }
}
