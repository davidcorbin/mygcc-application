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
- C++11 compiler for your target platform (GCC, Clang, MSVC, MinGW, etc.)

## Build on Ubuntu (recommended)
```sh
./scripts/build_ubuntu.sh
```

## Build on macOS
```sh
cd mygcc-application
git submodule update --init --recursive

mkdir build && cd build
cmake ..
cmake --build .
```

## Build on Windows
1. Install [CMake](https://cmake.org/download/), [Qt](https://www.qt.io/download), [Visual Studio](https://www.visualstudio.com/downloads/), and [Vcpkg](https://github.com/Microsoft/vcpkg).
    - Must install "MSVC 2015 32-bit" Qt library.
    - For Visual Studio, **Community** edition is fine, pick the "Desktop development with C++" option, or at least VC++.
    - Follow quick start instructions to install Vcpkg, making sure your install directory is that same as in CMakeLists.txt.
2. Update submodules: `git submodule update --init --recursive`
3. Using the **Qt Command Prompt** (Qt 32-bit for Desktop (MSVC)), navigate to the project directory, then run:
    - `mkdir build`
    - `cd build`
    - `cmake ..`
    - `cmake --build .`
4. Copy all resources from the folder and subfolders of `C:\mygcc-application\res\` to `C:\mygcc-application\build\Debug`
5. Copy needed DLLs from `C:\Qt\5.10.1\msvc2015\bin` to `C:\mygcc-application\build\Debug`
