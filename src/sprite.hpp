#ifndef IMPAC_SPRITE_HPP
#define IMPAC_SPRITE_HPP

#include <iostream>
#include <string>
#include <Magick++.h>

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
        sprite(const image_type& image, int x, int y);

        // Determines whether the given sprite intersects with this
        bool intersects(const sprite& that);

        // Gets the sprite's total area (width * height)
        int area() const;

        // Gets the sprite's width
        int width() const;

        // Gets the sprite's height
        int height() const;

        // Gets the sprite's right boundary (x + width)
        int right() const;

        // Gets the sprite's bottom boundary (y + height)
        int bottom() const;

        // Gets the sprite's internal image
        const image_type& image() const;

        // Sets the position of the sprite on the sprite sheet
        void set_position(int x, int y);

        int x;  // x position on the sprite sheet
        int y;  // y position on the sprite sheet
    private:
        image_type image_;  // internal image instance
    };

    std::ostream& operator<<(std::ostream& os, const sprite& s);
}

#endif // IMPAC_SPRITE_HPP
