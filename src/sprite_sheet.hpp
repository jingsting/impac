#ifndef IMPAC_SPRITE_SHEET_HPP
#define IMPAC_SPRITE_SHEET_HPP

#include <unordered_map>
#include "sprite.hpp"
#include "json.hpp"
using json = nlohmann::json;

namespace impac {
    // Represents a set of sprites and the maximum boundaries they can be packed
    // within. Each sprite is identified by a string tag that should be unique
    // among all sprites.
    class sprite_sheet {
    public:
        using image_type = sprite::image_type;
        using sprites_type = std::unordered_map<std::string, sprite>;

        // No default constructor.
        sprite_sheet() = delete;

        // Constructs an empty sprite sheet with a maximum width/height.
        sprite_sheet(size_t width, size_t height);

        // Constructs a sprite sheet with the given map of sprites and a
        // maximum width/height.
        sprite_sheet(sprites_type&& sprites, size_t width, size_t height);

        // Constructs a sprite sheet with the given map of images and a
        // maximum width/height.
        sprite_sheet(
            const std::unordered_map<std::string, image_type>& images,
            size_t width,
            size_t height);

        // Adds a sprite with an associated tag value if that tag doesn't
        // already exists. Returns a boolean indicating whether or not the
        // operation was successful.
        bool add_sprite(const std::string& tag, sprite&& sprite);

        // Adds a sprite with an associated tag value if that tag doesn't
        // already exists. Creates a new sprite from the given image. Returns
        // a boolean indicating whether or not the operation was successful.
        bool add_sprite(const std::string& tag, const image_type& image);

        // Gets the sprite sheet's map of sprites.
        sprites_type& sprites();
        const sprites_type& sprites() const;

        // Gets the sprite sheet's maximum width.
        size_t width() const;

        // Gets the sprite sheet's maximum height.
        size_t height() const;

        // Gets the sprite sheet's total width that's been consumed by sprites.
        size_t consumed_width() const;

        // Gets the sprite sheet's total height that's been consumed by sprites.
        size_t consumed_height() const;

        // Gets whether or not a sprite sheet has been packed.
        bool is_packed() const;

        // Packs the sprite sheet with a functor.
        template<typename F>
        bool pack(F f)
        {
            if ((is_packed_ = f(*this))) update_consumed_bounds();
            return is_packed_;
        }

        // Packs the sprite sheet and returns a complete image. `should_trim`
        // indicates whether or not the returned image should have the exact
        // dimensions of the sprite sheet or the minimum dimensions required
        // to fit all the sprites.
        template<typename F>
        image_type pack_into_image(F f, bool should_trim)
        {
            if (pack(f)) {
                image(should_trim);
            } else {
                throw "Not enough room to pack the sprite sheet";
            }
        }

        // Creates a composite image with all of the sprites on it. The
        // `should_trim` argument indicates whether the returned image should
        // have the same dimensions as the sprite sheet or the minimum
        // dimensions required to fit all the sprites.
        image_type image(bool should_trim) const;
    private:
        // Asserts the representation invariant
        void check_rep() const;

        // Update the space consumed by sprites.
        void update_consumed_bounds();

        sprites_type sprites_;    // map of sprites from name -> sprite
        size_t width_;            // max width of the sprite sheet
        size_t height_;           // max height of the sprite sheet
        size_t consumed_width_;   // consumed width from all sprites
        size_t consumed_height_;  // consumed height from all sprites
        bool is_packed_;          // has pack() been called yet
    };

    // JSON serialization of sprite sheets.
    void to_json(json& j, const sprite_sheet& ss);
}

#endif // IMPAC_SPRITE_SHEET_HPP
