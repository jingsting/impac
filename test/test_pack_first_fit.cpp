#include "catch.hpp"
#include "sprite_sheet.hpp"
#include "pack/first_fit.hpp"

TEST_CASE("first fit equal size square tiles", "[first_fit]") {
    // First-fit algorithm should place equal size square sprites in a perfect
    // grid assuming there is an appropriate amount of space. There should be
    // no bordering space between adjacent sprites.

    // Create an 100x100 sprite sheet and add 100, 10x10 identical square tiles
    auto image = Magick::Image{"10x10", "black"};
    auto sprite_sheet = impac::sprite_sheet{100, 100};
    for (auto i = size_t{0}; i < 100; ++i)
        sprite_sheet.add_sprite(std::to_string(i), image);

    // Pack the sprite sheet using the first-fit algorithm
    REQUIRE(sprite_sheet.pack(impac::pack::first_fit) == true);
    // Resulting width and height consumed should be exactly 100x100
    REQUIRE(sprite_sheet.consumed_width() == 100);
    REQUIRE(sprite_sheet.consumed_height() == 100);

    // Check sprite positions
    auto sprites = sprite_sheet.sprites();
    for (auto i = size_t{0}; i < 100; ++i) {
        auto sprite = sprites.at(std::to_string(i));
        // Position should be a perfect multiple of 10
        REQUIRE(sprite.x % 10 == 0);
        REQUIRE(sprite.y % 10 == 0);
        // Position should be within boundaries of sprite sheet
        REQUIRE(sprite.x >= 0);
        REQUIRE(sprite.right() <= 100);
        REQUIRE(sprite.y >= 0);
        REQUIRE(sprite.bottom() <= 100);
    }
}

TEST_CASE("first fit equal size rectangle tiles", "[first_fit]") {
    // First-fit algorithm should place equal size rectangle tiles in a perfect
    // grid assuming there is an appropriate amount of space. There should be
    // no bordering space between adjacent sprites.

    // Create an 100x100 sprite sheet and add 50, 10x20 identical tiles
    auto image = Magick::Image{"10x20", "black"};
    auto sprite_sheet = impac::sprite_sheet{100, 100};
    for (auto i = size_t{0}; i < 50; ++i)
        sprite_sheet.add_sprite(std::to_string(i), image);

    // Pack the sprite sheet using the first-fit algorithm
    REQUIRE(sprite_sheet.pack(impac::pack::first_fit) == true);
    // Resulting width and height should be exactly 100x100
    REQUIRE(sprite_sheet.consumed_width() == 100);
    REQUIRE(sprite_sheet.consumed_height() == 100);

    // Check sprite positions
    auto sprites = sprite_sheet.sprites();
    for (auto i = size_t{0}; i < 50; ++i) {
        auto sprite = sprites.at(std::to_string(i));
        // Position should be on 10x20 grid
        REQUIRE(sprite.x % 10 == 0);
        REQUIRE(sprite.y % 20 == 0);
        // Position should be within boundaries of sprite sheet
        REQUIRE(sprite.x >= 0);
        REQUIRE(sprite.right() <= 100);
        REQUIRE(sprite.y >= 0);
        REQUIRE(sprite.bottom() <= 100);
    }
}

TEST_CASE("first fit not enough space", "[first_fit]") {
    // Algorithm should fail if there isn't enough space available
    auto image = Magick::Image{"100x100", "black"};
    auto sprite_sheet = impac::sprite_sheet{10, 10};
    sprite_sheet.add_sprite("image", image);
    REQUIRE(sprite_sheet.pack(impac::pack::first_fit) == false);
}
