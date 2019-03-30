#include "sprite.hpp"

namespace impac {
    sprite::sprite(const image_type& image)
        : x{0}, y{0}, image_{image} {}

    sprite::sprite(const image_type& image, int x, int y)
        : x{x}, y{y}, image_{image} {}

    bool sprite::intersects(const sprite& that)
    {
        return (
            that.x < x + width() && x < that.x + that.width() &&
            that.y < y + height() && y < that.y + that.height());
    }

    int sprite::area() const { return width() * height(); }

    int sprite::width() const {  return image_.columns(); }

    int sprite::height() const { return image_.rows(); }

    int sprite::right() const { return x + width(); }

    int sprite::bottom() const { return y + height(); }

    const sprite::image_type& sprite::image() const { return image_; }

    void sprite::set_position(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    std::ostream& operator<<(std::ostream& os, const sprite& s)
    {
        return os << "sprite{x = " << s.x
                  << ", y = " << s.y
                  << ", width = " << s.width()
                  << ", height = " << s.height() << '}';
    }
}
