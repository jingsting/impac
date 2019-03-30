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

TEST_CASE("sprite set position", "[sprite]") {
    auto s = impac::sprite{Magick::Image{"10x10", "black"}};
    s.set_position(10, 10);
    REQUIRE(s.x == 10);
    REQUIRE(s.y == 10);
    s.set_position(3, 4);
    REQUIRE(s.x == 3);
    REQUIRE(s.y == 4);
    s.set_position(-19, -34);
    REQUIRE(s.x == -19);
    REQUIRE(s.y == -34);
}

TEST_CASE("sprite intersection", "[sprite]") {
    auto s1 = impac::sprite{Magick::Image{"10x20", "black"}};
    auto s2 = impac::sprite{Magick::Image{"20x10", "black"}};

    // Test every possible intersecting position between s1 and s2, and the
    // boundary conditions of the intersection problem.
    for (auto x = int{-20}; x <= 10; ++x) {
        for (auto y = int{-10}; y <= 20; ++y) {
            s2.set_position(x, y);
            if (x == -20 || x == 10 || y == -10 || y == 20) {
                // Sprite boundaries are directly adjacent but don't intersect
                REQUIRE(s1.intersects(s2) == false);
                REQUIRE(s2.intersects(s1) == false);
            } else {
                // Sprite boundaries overlap
                REQUIRE(s1.intersects(s2) == true);
                REQUIRE(s2.intersects(s1) == true);
            }
        }
    }
}
