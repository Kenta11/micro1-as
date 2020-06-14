# micro1-as

[![Ubuntu](https://github.com/Kenta11/micro1-as/workflows/Ubuntu/badge.svg)](https://github.com/Kenta11/micro1-as)
[![Travis CI](https://travis-ci.org/Kenta11/micro1-as.svg?branch=master)](https://travis-ci.org/Kenta11/micro1-as)
[![Circle CI](https://circleci.com/gh/Kenta11/micro1-as.svg?style=svg)](https://circleci.com/gh/Kenta11/micro1-as)

This project is a MICRO-1 assembler written in C++17. It uses only C++17 standard libraries, so it is easy to understand. It can be used in Windows and Linux environments.

## Quick building

```
$ git pull --recursive https:://github.com/Kenta11/micro1-as
$ cd micro1-as
$ source ./script/build.sh
```

After compiling, you can find out `micro1-as` program under `bin/`.

## Environments

### Windows 10

- Visual Studio 2019

### Linux (Ubuntu / ManjaroLinux)

- CMake (3.10 >=)
- g++ (which supports C++17)

## Tests

### Unit tests

If you want to unit-test C++ source code, add `BUILD_UNIT_TESTS` option to cmake command.

```
$ mkdir build # in micro1-as directory
$ cd build
$ cmake -DBUILD_UNIT_TESTS=ON ..
$ make -j`nproc`; ctest
```

## License

Files are released under the [MIT license](LICENSE). However, the license is not applied to third-party libraries.

## Contact

- Twitter: [isKenta14](https://twitter.com/isKenta14)
