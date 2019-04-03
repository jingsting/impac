[![Build Status](https://travis-ci.com/ethanlynn/impac.svg?branch=master)](https://travis-ci.com/ethanlynn/impac)

# impac

Im(age) Pac(ker)

## Decription:
This project takes individual images and creates a sprite sheet or texture atlas. The goal of this project is to reduce load time when one needs to upload many images into an application or program. This is done by taking the images needed and placing them together in such a way that they fit into the smallest single image possible. This project is a command line tool and can be built on any platform.

## Building

### Build Dependencies

- [CMake](https://cmake.org/)
- [Magick++](https://imagemagick.org/Magick++/)
- [Boost.Filesystem](https://www.boost.org/doc/libs/1_69_0/libs/filesystem/doc/index.htm)

### Build Instructions

```
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
```

### Running

Go to build directory if not already(`cd build`),

```
$ ./impac /path/to/**/directory
```


## Communication
* Our [Mattermost channel](https://chat.rcos.io/open-source/channels/impac) is a great place to get in contact with us, ask questions, and see the direction of our project!
* Feel free to check out our [RPI Observatory page](https://rcos.io/projects/ethanlynn/impac/profile) for more information regarding us


## Contributing
* Visit our [issue tracker](https://github.com/ethanlynn/impac/issues) to see some current bugs we are solving
* Please read our [CODE_OF_CONDUCT.md](https://github.com/ethanlynn/impac/blob/master/CODE_OF_CONDUCT.md) for more details and the process for submitting issues to us.

## Authors

* **Allison Ariemma**
* **Ethan Lynn**
* **Alex Monaco**
* **Jingfei Zhou**

See also the list of [contributors](https://github.com/ethanlynn/impac/graphs/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [license](LICENSE) file for details
