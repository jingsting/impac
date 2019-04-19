# impac

![Sprite Sheet Example](docs/images/sprite-sheet-example.jpg)

[![Build Status](https://travis-ci.com/ethanlynn/impac.svg?branch=master)](https://travis-ci.com/ethanlynn/impac)

## Description

This project takes individual images and creates a sprite sheet or texture atlas. The goal of this project is to reduce load time when one needs to upload many images into an application or program. This is done by taking the images needed and placing them together in such a way that they fit into the smallest single image possible. This project is a command line tool and can be built on any platform.

## Running

```
Usage:
  impac <input-directory> <output-directory>

Options:
  --size=<width>,<height>     The size of the sprite sheet [default: minimum size possible].
  --image=<name>.<extension>  The name of the sprite sheet image file [default: sprite-sheet.png]
  --data=<name>.<extension>   The name of the sprite sheet data file [default: sprite-sheet.json]
  --algorithm=<algorithm>     The name of the packing algorithm to use [default: first-fit]
```

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
