# Facade
[![Build Status](https://travis-ci.com/davidcorbin/mygcc-application.svg?token=dxqddm4qxdWvzPBrhpv6&branch=master)](https://travis-ci.com/davidcorbin/mygcc-application)

The desktop interface to myGCC.

## Supported systems
- Windows 10
- Ubuntu
- macOS

## Requirements
- Qt 5.2 or later
- CMake 3.0 or later
- C++11 compiler for your target platform (GCC, Clang, MVSC, MinGW, etc.)

## Build on Ubuntu (recommended)
```sh
./scripts/build_ubuntu.sh
```

## Build on Windows

## Build on macOS
```sh
cd mygcc-application
git submodule update --init --recursive

mkdir build && cd build
cmake ..
cmake --build .
```
