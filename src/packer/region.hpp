#ifndef IMPAC_region_HPP
#define IMPAC_region_HPP

#include <algorithm>
#include <cassert>
#include <type_traits>

namespace impac {
    // Templated rectangle class used by the packing algorithm to define a
    // (x, y, width, height) region of an image. The template parameter T should
    // be an arithmetic type. Width and height are always >= 0.
    template<
        typename T,
        typename U,
        typename std::enable_if_t<std::is_arithmetic_v<U>>>
    class region {
    public:
        // No default constructor
        region() = delete;

        // Default copy & move semantics
        region(const region&) = default;
        region& operator=(const region&) = default;
        region(const region&&) = default;
        region& operator=(const region&&) = default;

        // Construct a region with a tag, x, y, width, and height
        region(const T& tag, U x, U y, U width, U height)
            : tag_{tag},
              x_{x},
              y_{y},
              width_{width},
              height_{height} 
        {
            assert(width_ >= 0);
            assert(height_ >= 0);
        }

        // Determines if the given region intersects with this.
        bool intersects(const region<T, U>& that)
        {
            return (
                that.x_ < x_ + width_ && x_ < that.x_ + that.width_ &&
                that.y_ < y_ + height_ && y_ < that.y_ + that.height_);
        }

        // Computes the area of the region.
        U area() const { return width_ * height_; }

        const T& tag() const { return tag_; }
        U x() const { return x_; }
        U y() const { return y_; }
        U width() const { return width_; }
        U height() const { return height_; }
        U right() const { return x_ + width_; }
        U bottom() const { return y_ + height_; }

        void set_x(U x) { x_ = x; }
        void set_y(U y) { y_ = y; }
        void set_position(U x, U y) { x_ = x; y_ = y; }
    private:
        const T tag_;     // tag used to identify region
        U x_;             // left x-position of the region
        U y_;             // top y-position of the region
        const U width_;   // width of the region (>= 0)
        const U height_;  // height of the region (>= 0)
    };
}

#endif
