#ifndef IMPAC_REGION_HPP
#define IMPAC_REGION_HPP

#include <algorithm>
#include <cassert>
#include <iostream>
#include <type_traits>

namespace impac {
    // Describes a (x, y, width, height) identified by a tag value. Used by
    // the packer classes to associate a given image to a placement within a
    // texture atlas.
    template<typename T, typename U>
    class region {
    public:
        using type = region<T, U>;

        // No default constructor
        region() = delete;

        // Default copy/move semantics
        region(const type&) = default;
        region& operator=(const type&) = default;
        region(type&&) = default;
        region& operator=(type&&) = default;

        // Constructs a region with a tag, x, y, width, and height
        region(T tag, U x, U y, U width, U height)
            : tag_{tag}, x_{x}, y_{y}, width_{width}, height_{height} 
        {
            assert(width_ >= 0 && height_ >= 0);
        }

        // Determines if the given region intersects
        bool intersects(const type& that)
        {
            return (
                that.x_ < x_ + width_ && x_ < that.x_ + that.width_ &&
                that.y_ < y_ + height_ && y_ < that.y_ + that.height_);
        }

        // Calculates the area
        U area() const { return width_ * height_; }

        // Gets the tag
        const T& tag() const { return tag_; }

        // Gets the x/left position
        U x() const { return x_; }

        // Gets the y/top position
        U y() const { return y_; }

        // Gets the width
        U width() const { return width_; }

        // Gets the height
        U height() const { return height_; }

        // Gets the right position (left + width)
        U right() const { return x_ + width_; }

        // Gets the bottom position (top + height)
        U bottom() const { return y_ + height_; }

        // Sets the x/left position
        void set_x(U x) { x_ = x; }

        // Sets the y/top position
        void set_y(U y) { y_ = y; }

        // Sets the (x, y)/(top, left) position
        void set_position(U x, U y)
        {
            x_ = x;
            y_ = y;
        }

        // Sets the width
        void set_width(U width)
        {
            width_ = width;
            assert(width_ >= 0);
        }

        // Sets the height
        void set_height(U height)
        {
            height_ = height;
            assert(height_ >= 0);
        }

        // Sets the dimensions
        void set_size(U width, U height)
        {
            width_ = width;
            height_ = height;
            assert(width_ >= 0 && height_ >= 0);
        }
    private:
        T tag_;     // tag used to identify region
        U x_;       // left x-position of the region
        U y_;       // top y-position of the region
        U width_;   // width of the region (>= 0)
        U height_;  // height of the region (>= 0)
    };

    template<typename T, typename U>
    std::ostream& operator<<(std::ostream& os, const region<T, U>& region)
    {
        os << "{tag = '" << region.tag()
           << "', x = " << region.x()
           << ", y = " << region.y()
           << ", width = " << region.width()
           << ", height = " << region.height() << '}';
        return os;
    }
}

#endif
