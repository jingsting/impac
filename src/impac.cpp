#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <string>
#include "Magick++.h"
#include "boost/filesystem.hpp"
#include "sprite_sheet.hpp"
#include "pack/first_fit.hpp"
#include "pack/first_fit_v2.hpp"

namespace fs = boost::filesystem;

// default width and height for the sprite sheet
size_t DEFAUT_WIDTH = 2048;
size_t DEFAUT_HEIGHT = 2048;

// Program usage instructions.
constexpr static auto usage = (
    "Usage:\n"
    "  impac <input-directory> <output-directory>\n"
    "\n"
    "Options:\n"
    "  --size=<width>,<height>     The size of the sprite sheet [default: "
    "minimum size possible].\n"
    "  --image=<name>.<extension>  The name of the sprite sheet image file "
    "[default: sprite-sheet.png]\n"
    "  --data=<name>.<extension>   The name of the sprite sheet data file "
    "[default: sprite-sheet.json]\n"
    "  --algorithm=<algorithm>     The name of the packing algorithm to use "
    "[default: first-fit]\n"
);

// Array of supported image file extensions.
constexpr static auto supported_image_extensions = {
    ".png",
    ".jpg",
    ".jpeg",
    ".bmp",
    ".ppm",
    ".webp",
    ".tiff",
    ".gif"
};

// Array of supported data file extensions.
constexpr static auto supported_data_extensions = {
    ".json",
    ".xml"
};

// Array of supported algorithm names.
constexpr static auto supported_algorithms = {
    "first-fit",
    "first-fit-v2"
};

// Checks whether the given file extension is a supported image file extension.
bool is_supported_image_extension(const fs::path& extension)
{
    for (const auto* e : supported_image_extensions)
        if (extension == e)
            return true;
    return false;
}

// Checks whether the given file extension is a supported data file extension.
bool is_supported_data_extension(const fs::path& extension)
{
    for (const auto* e : supported_data_extensions)
        if (extension == e)
            return true;
    return false;
}

// Checks whether the given algorithm name is a supported algorithm.
bool is_supported_algorithm(const std::string& algorithm)
{
    for (const auto* a : supported_algorithms)
        if (algorithm == a)
            return true;
    return false;
}

int main(int argc, const char** argv)
{
    if (argc < 3) {
        std::cout << usage;
        return 0;
    }

    // Positional arguments for <input-directory> and <output-directory>.
    const auto input_path = fs::path{argv[1]};
    const auto output_path = fs::path{argv[2]};

    // Default values for command line options.
    auto width = DEFAUT_WIDTH;
    auto height = DEFAUT_HEIGHT;
    size_t max_image_width = 0;
    size_t max_image_height = 0;
    auto should_trim = true;
    auto image_path = output_path / "sprite-sheet.png";
    auto data_path = output_path / "sprite-sheet.json";
    auto algorithm = std::string{"first-fit"};

    // Override default values with user-specified options.
    for (auto i = int{3}; i < argc; ++i) {
        const auto* arg = argv[i];
        if (std::strncmp(arg, "--size=", 7) == 0) {
            // Parse sprite sheet size in form "--size=<width>,<height>".
            auto ss = std::stringstream{arg + 7};
            if (!(ss >> width)) {
                std::cerr << "Error: Invalid argument `" << arg << "`."
                          << std::endl;
                return 1;
            }
            if (ss.peek() == ',') ss.ignore();
            if (!(ss >> height)) {
                std::cerr << "Error: Invalid argument `" << arg << "`."
                          << std::endl;
                return 1;
            }
            // If the user specified an exact size, we don't want to trim the
            // sprite sheet after packing.
            should_trim = false;
        } else if (std::strncmp(arg, "--image=", 8) == 0) {
            // Parse image name in form "--image=<name>.<extension>".
            const auto* image_name = arg + 8;
            image_path = output_path / image_name;
            // Make sure image file extension is supported.
            if (!is_supported_image_extension(image_path.extension())) {
                std::cerr << "Error: Unsupported image extension "
                          << image_path.extension() << '.' << std::endl;
                return 1;
            }
        } else if (std::strncmp(arg, "--data=", 7) == 0) {
            // Parse data name in form "--data=<name>.<extension>".
            const auto* data_name = arg + 7;
            data_path = output_path / data_name;
            // Make sure data file extension is supported.
            if (!is_supported_data_extension(data_path.extension())) {
                std::cerr << "Error: Unsupported data extension "
                          << data_path.extension() << '.' << std::endl;
                return 1;
            }
        } else if (std::strncmp(arg, "--algorithm=", 12) == 0) {
            algorithm = std::string{arg + 12};
            if (!is_supported_algorithm(algorithm)) {
                std::cerr << "Error: Unsupported algorithm '" << algorithm
                          << "'." << std::endl;
            }
        } else {
            std::cerr << "Error: Unexpected argument `" << arg << "`."
                      << std::endl;
            return 1;
        }
    }

    // Read images from the input directory and populate a new sprite sheet.
    auto sprite_sheet = impac::sprite_sheet{width, height};
    try {
        for (const auto& entry : fs::directory_iterator{input_path}) {
            auto entry_path = entry.path();
            // Add the directory entry to the sprite sheet if it is a file with
            // one of the supported image file extensions.
            if (fs::is_regular_file(entry) &&
                    is_supported_image_extension(entry_path.extension())) {
                auto image = Magick::Image{};
                image.read(entry_path.native());
                sprite_sheet.add_sprite(entry_path.filename().native(), image);
                max_image_width = std::max(max_image_width, image.columns());
                max_image_height = std::max(max_image_height, image.rows());
            }
        }
    } catch (const fs::filesystem_error& error) {
        std::cerr << "Error: " << error.what() << std::endl;
        return 1;
    }

    if (max_image_width>width || max_image_height>height) {
        std::cerr << "Error: Some sprites exceeded sprite sheet's dimension." << std::endl;
        return 1;
    }

    // Pack the sprite sheet using the given algorithm. (Only one possibility
    // right now).
    bool success = false;
    try {
        if (algorithm == "first-fit") {
            success = sprite_sheet.pack(impac::pack::first_fit);
        } else if (algorithm == "first-fit-v2") {
            success = sprite_sheet.pack(impac::pack::first_fit_v2);
        } else {
            success = sprite_sheet.pack(impac::pack::first_fit);
        }
    } catch (const std::string& error) {
        std::cerr << "Error: " << error << std::endl;
        return 1;
    }
    if (!success) {
        std::cerr << "Error: Not enough space to pack sprites." << std::endl;
        return 1;
    }

    // Generate the output image and save it to the image path.
    auto image = sprite_sheet.image(should_trim);
    image.write(image_path.native());

    // Generate the output data and save it to the output path.
    auto data = std::ofstream{data_path.native()};
    if (data_path.extension() == ".json") {
        data << json(sprite_sheet);
    } else if (data_path.extension() == ".xml") {
        data << "<error>UNIMPLEMENTED</error>" << std::endl;
    }
    data.close();
}
