#ifndef IMPAC_SPRITE_HPP
#define IMPAC_SPRITE_HPP

#include <iostream>
#include <string>
#include <Magick++.h>
#include "json.hpp"
using json = nlohmann::json;

namespace impac {
    // Represents a single sprite on a sprite sheet with an image and its (x, y)
    // position on a sprite sheet.
    class sprite {
    public:
        using image_type = Magick::Image;

        // No default constructor
        sprite() = delete;

        // Default copy/move semantics
        sprite(const sprite&) = default;
        sprite& operator=(const sprite&) = default;
        sprite(sprite&&) = default;
        sprite& operator=(sprite&&) = default;

        // Constructs a sprite with the given image at the origin
        explicit sprite(const image_type& image);

        // Constructs a sprite with the given image and (x, y) position
        sprite(const image_type& image, size_t x, size_t y);

        // Determines whether the given sprite intersects with this
        bool intersects(const sprite& that);

        // Gets the sprite's total area (width * height)
        size_t area() const;

        // Gets the sprite's width
        size_t width() const;

        // Gets the sprite's height
        size_t height() const;

        // Gets the sprite's right boundary (x + width)
        size_t right() const;

        // Gets the sprite's bottom boundary (y + height)
        size_t bottom() const;

        // Gets the sprite's internal image
        const image_type& image() const;

        // Sets the position of the sprite on the sprite sheet
        void set_position(size_t x, size_t y);

        size_t x;  // x position on the sprite sheet
        size_t y;  // y position on the sprite sheet
    private:
        image_type image_;  // internal image instance
    };

    // Debug formatting of sprite objects.
    std::ostream& operator<<(std::ostream& os, const sprite& s);

    // JSON serialization of sprite objects.
    void to_json(json& j, const sprite& s);
}

#endif // IMPAC_SPRITE_HPP
