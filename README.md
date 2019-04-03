[![Build Status](https://travis-ci.com/ethanlynn/impac.svg?branch=master)](https://travis-ci.com/ethanlynn/impac)

# impac

Impac is a small CLI application for creating [sprite sheets/texture atlases](https://en.wikipedia.org/wiki/Texture_atlas) from a set of source images. Command line options are available for controlling the output format of the sprite sheet and the parameters of the packing algorithm. (See [usage](#usage) for more detailed instructions.)

## Motivation

Sprite sheets (also called texture atlases) are the combination of many small images into a composite image along with encoded information about where the smaller images are. This concept is useful for several different reasons:

- In graphics-intensive applications, rendering many small subsections of a single image is more efficient than rendering multiple individual images due to increased memory locality on the GPU. This technique is commonly found in 2D games.

- When loading many small images over HTTP, it reduces latency to bundle these images into a single HTTP request. This is frequently done in web applications where there are many icons or UI elements.

In order to make an optimal sprite sheet, the goal is to reduce the final amount of area needed to pack all the individual images into. The packing algorithm must decide where to place each of the individual images so that they fit together in the most compact way possible without destroying the integrity of the original images. Existing products such as [TexturePacker](https://www.codeandweb.com/texturepacker) accomplish this but are only available under a freemium business model. Our goal is to implement some of this functionality in an open-source project that is [freely](LICENSE) available to the community.

## Usage

Right now impac is in its infancy and only supports one configuration:
```
$ ./impac ./path/to/folder/of/images ./path/to/output
```
This command takes images from the input directory and creates a sprite sheet in the output directory along with a JSON file encoding the layout of the sprite sheet.

## Building

### Build Dependencies

- Compiler with C++17 support
- [CMake](https://cmake.org/)
- [Magick++](https://imagemagick.org/Magick++/)
- [Boost.Filesystem](https://www.boost.org/doc/libs/1_69_0/libs/filesystem/doc/index.htm)

Installing dependencies on MacOS via `homebrew`:
```
$ brew update
$ brew install cmake
$ brew install boost
$ brew install imagemagick
```

Installing dependencies on Debian/Ubuntu via `apt`:
```
$ sudo apt install libboost-all-dev
$ sudo apt install libmagick++-dev
```

### Build Instructions

```
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
```

This generates a main executable named `impac` and test target named `test` under the build directory.

## Communication

* Our [Mattermost channel](https://chat.rcos.io/open-source/channels/impac) is a great place to get in contact with us, ask questions, and see the direction of our project!
* Feel free to check out our [RPI Observatory page](https://rcos.io/projects/ethanlynn/impac/profile) for more information regarding us.

## Contributing

* Visit our [issue tracker](https://github.com/ethanlynn/impac/issues) to see some current bugs we are solving.
* Please read our [code of conduct](https://github.com/ethanlynn/impac/blob/master/CODE_OF_CONDUCT.md) for more details and the process for submitting issues to us.

## Authors

* **Allison Ariemma**
* **Ethan Lynn**
* **Alex Monaco**
* **Jingfei Zhou**

See also the list of [contributors](https://github.com/ethanlynn/impac/graphs/contributors) who participated in this project.

## License

This project is licensed under the [MIT License](LICENSE).
