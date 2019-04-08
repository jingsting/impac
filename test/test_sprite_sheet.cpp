#include <unordered_map>
#include "catch.hpp"
#include "Magick++.h"
#include "sprite_sheet.hpp"
#include "pack/first_fit.hpp"

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
        const auto& sprite1 = sprites1.at(key);
        const auto& sprite2 = sprites2.at(key);
        REQUIRE(sprite1.x == 0);
        REQUIRE(sprite1.y == 0);
        REQUIRE(sprite1.width());
        REQUIRE(sprite1.height());
        REQUIRE(sprite1.image() == sprite2.image());
    }
}

TEST_CASE("sprite sheet image creation", "[sprite_sheet]") {
    auto image1 = Magick::Image{"10x10", "black"};
    auto image2 = Magick::Image{"10x10", "white"};
    auto sprite1 = impac::sprite{image1};
    auto sprite2 = impac::sprite{image2};
    auto sprite_sheet = impac::sprite_sheet{100, 100};
    sprite_sheet.add_sprite("sprite1", std::move(sprite1));
    sprite_sheet.add_sprite("sprite2", std::move(sprite2));
    if (sprite_sheet.pack(impac::pack::first_fit) == true) {
        auto composite_image = sprite_sheet.image(true);
        REQUIRE(composite_image.columns() == 20);
        REQUIRE(composite_image.rows() == 10);
    }
}

TEST_CASE("sprite sheet JSON serialization", "[sprite_sheet]") {
    auto sprite_sheet = impac::sprite_sheet{100, 100};
    sprite_sheet.add_sprite("sprite1", impac::sprite{{"10x10", "black"}});
    sprite_sheet.add_sprite("sprite2", impac::sprite{{"10x10", "white"}});
    sprite_sheet.pack(impac::pack::first_fit);
    auto j = json(sprite_sheet);
    auto frames = j["frames"];
    for (auto& [_, value] : frames.items()) {
        REQUIRE(value.at("width") == 10);
        REQUIRE(value.at("height") == 10);
    }
}
