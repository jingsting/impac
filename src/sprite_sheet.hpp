#ifndef IMPAC_SPRITE_SHEET_HPP
#define IMPAC_SPRITE_SHEET_HPP

#include <unordered_map>
#include "sprite.hpp"

namespace impac {
    // Represents a set of sprites and the maximum boundaries they can be packed
    // within. Each sprite is identified by a string tag that should be unique
    // among all sprites.
    class sprite_sheet {
    public:
        using image_type = sprite::image_type;
        using sprites_type = std::unordered_map<std::string, sprite>;

        // No default constructor
        sprite_sheet() = delete;

        // Constructs an empty sprite sheet with a maximum width/height
        sprite_sheet(int width, int height);

        // Constructs a sprite sheet with the given map of sprites and a
        // maximum width/height
        sprite_sheet(
            sprites_type&& sprites,
            int width,
            int height);

        // Constructs a sprite sheet with the given map of images and a
        // maximum width/height
        sprite_sheet(
            const std::unordered_map<std::string, image_type>& images,
            int width,
            int height);
        
        // Adds a sprite with an associated tag value if that tag doesn't
        // already exists. Returns a boolean indicating whether or not the
        // operation was successful.
        bool add_sprite(const std::string& tag, sprite&& sprite);

        // Adds a sprite with an associated tag value if that tag doesn't
        // already exists. Creates a new sprite from the given image. Returns
        // a boolean indicating whether or not the operation was successful.
        bool add_sprite(const std::string& tag, const image_type& image);

        // Gets the sprite sheet's map of sprites
        sprites_type& sprites();

        // Gets the sprite sheet's maximum width
        int width() const;

        // Gets the sprite sheet's maximum height
        int height() const;
    private:
        // Asserts the representation invariant
        void check_rep() const;

        sprites_type sprites_;  // map of sprites from sprite tag to sprite
        int width_;             // available width of the sprite sheet
        int height_;            // available height of the sprite sheet
    };
}

#endif // IMPAC_SPRITE_SHEET_HPP
