#include "sprite.hpp"

namespace impac {
    sprite::sprite(const image_type& image)
        : x{0}, y{0}, image_{image} {}

    sprite::sprite(const image_type& image, size_t x, size_t y)
        : x{x}, y{y}, image_{image} {}

    bool sprite::intersects(const sprite& that)
    {
        return (
            that.x < x + width() && x < that.x + that.width() &&
            that.y < y + height() && y < that.y + that.height());
    }

    size_t sprite::area() const { return width() * height(); }

    size_t sprite::width() const {  return image_.columns(); }

    size_t sprite::height() const { return image_.rows(); }

    size_t sprite::right() const { return x + width(); }

    size_t sprite::bottom() const { return y + height(); }

    const sprite::image_type& sprite::image() const { return image_; }

    void sprite::set_position(size_t x, size_t y)
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

    void to_json(json& j, const sprite& s)
    {
        j["x"] = s.x;
        j["y"] = s.y;
        j["width"] = s.width();
        j["height"] = s.height();
    }
}
