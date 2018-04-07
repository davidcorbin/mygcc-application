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
1. Install [CMake](https://cmake.org/download/), [Qt5](https://www.qt.io/download), [Visual Studio](https://www.visualstudio.com/downloads/).
    - Must install "MSVC 2015 32-bit" Qt library.
    - For Visual Studio, **Community** edition is fine, pick the "Desktop development with C++" option, or at least VC++.
    - You must add Qt to the path (`setx CMAKE_PREFIX_PATH "C:\Qt\5.10.1\msvc2015"`)
2. Using the **Qt Command Prompt** (Qt 32-bit for Desktop (MSVC)), navigate to the project directory, then run:
    - `mkdir build`
    - `cd build`
    - `cmake ..`
    - `cmake --build .` (or `msbuild /m facade-application.sln` in VS developer command prompt for multicore building)
3. Copy all resources from the folder and subfolders of `C:\mygcc-application\res\` to `C:\mygcc-application\build\Debug`
4. Include `mygcc-api-with-dependencies.jar` from [mygcc-api](https://github.com/davidcorbin/mygcc-api).
5. Copy needed DLLs from `C:\Qt\5.10.1\msvc2015\bin` to `C:\mygcc-application\build\Debug`

## Build Documentation
Generating documentation requires Doxygen

    doxygen scripts/Doxyfile
