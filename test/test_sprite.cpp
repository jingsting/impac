#include "catch.hpp"
#include "Magick++.h"
#include "sprite.hpp"

TEST_CASE("sprite constructor", "[sprite]") {
    auto image = Magick::Image{"10x15", "white"};

    SECTION("image") {
        auto sprite = impac::sprite{image};
        REQUIRE(sprite.x == 0);
        REQUIRE(sprite.y == 0);
        REQUIRE(sprite.width() == 10);
        REQUIRE(sprite.height() == 15);
        REQUIRE(sprite.image() == image);
    }

    SECTION("image with coordinates") {
        auto sprite = impac::sprite{image, 20, 30};
        REQUIRE(sprite.x == 20);
        REQUIRE(sprite.y == 30);
        REQUIRE(sprite.width() == 10);
        REQUIRE(sprite.height() == 15);
        REQUIRE(sprite.image() == image);
    }

    SECTION("copy") {
        auto s1 = impac::sprite{image};
        auto s2 = impac::sprite{s1};
        REQUIRE(s1.x == s2.x);
        REQUIRE(s1.y == s2.y);
        REQUIRE(s1.width() == s2.width());
        REQUIRE(s1.height() == s2.height());
        REQUIRE(s1.image() == s2.image());
    }

    SECTION("move") {
        auto s1 = impac::sprite{image};
        auto s2 = impac::sprite{std::move(s1)};
        REQUIRE(s1.x == s2.x);
        REQUIRE(s1.y == s2.y);
        REQUIRE(s1.width() == s2.width());
        REQUIRE(s1.height() == s2.height());
        REQUIRE(s1.image() == s2.image());
    }
}

TEST_CASE("sprite area is calculated correctly", "[sprite]") {
    auto i1 = Magick::Image{"20x30", "white"};
    auto i2 = Magick::Image{"30x40", "white"};
    auto s1 = impac::sprite{i1};
    auto s2 = impac::sprite{i2};
    REQUIRE(s1.area() == 600);
    REQUIRE(s2.area() == 1200);
}
