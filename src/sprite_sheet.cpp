#include <cassert>
#include <algorithm>
#include "sprite_sheet.hpp"

namespace impac {
    sprite_sheet::sprite_sheet(size_t width, size_t height)
        : sprites_{},
          width_{width},
          height_{height},
          consumed_width_{0},
          consumed_height_{0},
          is_packed_{false}
    {
        check_rep();
    }

    sprite_sheet::sprite_sheet(
        sprites_type&& sprites,
        size_t width,
        size_t height)
        : sprites_{sprites},
          width_{width},
          height_{height},
          consumed_width_{0},
          consumed_height_{0},
          is_packed_{false}
    {
        check_rep();
    }

    sprite_sheet::sprite_sheet(
        const std::unordered_map<std::string, image_type>& images,
        size_t width,
        size_t height)
        : sprites_{images.size()},
          width_{width},
          height_{height},
          consumed_width_{0},
          consumed_height_{0}
    {
        for (const auto& [tag, image] : images) {
            if (!add_sprite(tag, image)) {
                throw "Sprites must all have unique names";
            }
        }
        check_rep();
    }

    bool sprite_sheet::add_sprite(const std::string& tag, sprite&& sprite)
    {
        if (sprites_.emplace(tag, sprite).second) {
            update_consumed_bounds();
            return true;
        }
        return false;
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

    size_t sprite_sheet::width() const { return width_; }

    size_t sprite_sheet::height() const { return height_; }

    size_t sprite_sheet::consumed_width() const { return consumed_width_; }

    size_t sprite_sheet::consumed_height() const { return consumed_height_; }

    bool sprite_sheet::is_packed() const { return is_packed_; }

    sprite_sheet::image_type sprite_sheet::image(bool should_trim) const
    {
        // Make sure we've packed the sprite sheet before attempting to create
        // an image from it.
        assert(is_packed());
        size_t total_width = should_trim ? consumed_width_ : width_;
        size_t total_height = should_trim ? consumed_height_ : height_;
        // Create a composite image of all of the sprite images.
        auto composite_image = Magick::Image{
            {total_width, total_height}, "transparent"};
        for (const auto& [_, sprite] : sprites_) {
            composite_image.composite(sprite.image(), sprite.x, sprite.y);
        }
        return composite_image;
    }

    void sprite_sheet::update_consumed_bounds()
    {
        consumed_width_ = 0;
        consumed_height_ = 0;
        for (const auto& [_, sprite] : sprites_) {
            consumed_width_ = std::max(consumed_width_, sprite.right());
            consumed_height_ = std::max(consumed_height_, sprite.bottom());
        }
    }

    void sprite_sheet::check_rep() const
    {
        assert(width_ >= 0);
        assert(height_ >= 0);
        assert(0 <= consumed_width_ && consumed_width_ <= width_);
        assert(0 <= consumed_height_ && consumed_height_ <= height_);
    }

/*
    void to_json(json& j, const sprite_sheet& ss)
    {
        assert(ss.is_packed());
        j = json{{"frames", ss.sprites()}};
    }
*/
}
