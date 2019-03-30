#include <unordered_map>
#include "catch.hpp"
#include "Magick++.h"
#include "sprite_sheet.hpp"

TEST_CASE("sprite sheet constructor", "[sprite_sheet]") {
    auto images = std::unordered_map<std::string, Magick::Image>{
        {"1.png", {"10x10", "black"}},
        {"2.png", {"10x10", "black"}},
        {"3.png", {"10x10", "black"}},
        {"4.png", {"10x10", "black"}}};

    SECTION("empty") {
        auto sprite_sheet = impac::sprite_sheet{100, 100};
        REQUIRE(sprite_sheet.width() == 100);
        REQUIRE(sprite_sheet.height() == 100);
        REQUIRE(sprite_sheet.sprites().size() == 0);
    }

    SECTION("images") {
        auto sprite_sheet = impac::sprite_sheet{images, 100, 100};
        REQUIRE(sprite_sheet.width() == 100);
        REQUIRE(sprite_sheet.height() == 100);
        REQUIRE(sprite_sheet.sprites().size() == 4);
    }
}

TEST_CASE("sprite sheet add sprite", "[sprite_sheet]") {

    auto sprite_sheet1 = impac::sprite_sheet{100, 100};
    auto sprite_sheet2 = impac::sprite_sheet{100, 100};

    for (auto i = int{10}; i < 100; ++i) {
        auto size = static_cast<size_t>(i);
        auto image = Magick::Image{{size, size}, "black"};
        auto key = std::to_string(i);
        sprite_sheet1.add_sprite(key, impac::sprite{image});
        sprite_sheet2.add_sprite(key, image);
    }

    auto sprites1 = sprite_sheet1.sprites();
    auto sprites2 = sprite_sheet2.sprites();
    for (auto i = int{10}; i < 100; ++i) {
        auto key = std::to_string(i);
        auto sprite1 = sprites1.at(key);
        auto sprite2 = sprites2.at(key);
        REQUIRE(sprite1.x == 0);
        REQUIRE(sprite1.y == 0);
        REQUIRE(sprite1.width());
        REQUIRE(sprite1.height());
        REQUIRE(sprite1.image() == sprite2.image());
    }
}
