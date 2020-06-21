# micro1-as

[![Ubuntu](https://github.com/Kenta11/micro1-as/workflows/Ubuntu/badge.svg)](https://github.com/Kenta11/micro1-as)
[![Travis CI](https://travis-ci.org/Kenta11/micro1-as.svg?branch=master)](https://travis-ci.org/Kenta11/micro1-as)
[![Circle CI](https://circleci.com/gh/Kenta11/micro1-as.svg?style=svg)](https://circleci.com/gh/Kenta11/micro1-as)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

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
- g++ or clang++

## Tests

### Unit tests

If you want to unit-test C++ source code, run `source ./script/unittest.sh`.

```
$ source ./script/unittest.sh
```

### System tests

If you want to system-test, run `source ./script/build.sh; source ./script/systemtest.sh`.

```
$ source ./script/build.sh
$ source ./script/systemtest.sh
```

## License

Files are released under the [MIT license](LICENSE). However, the license is not applied to third-party libraries.

## Contact

- Twitter: [isKenta14](https://twitter.com/isKenta14)
