# Deployment

## Requirements
- Qt Installer Framework (v3.0.2 or later)
    - Add `bin` directory to `$PATH`

## macOS

#### Create release binary
To create the release version of Facade, run CMake with the build type Release.

```sh
mkdir Release
cd Release
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

#### Create installer
1. Copy the release build of the application (`facade.app`) from the `Release/` directory to `package/packages/com.corbinharvey.facade/data`
1. `cd packages`
1. `binarycreator -c config/config.xml -p packages FacadeInstaller-<version>`

## Windows

#### Create release binary

```sh
mkdir Release
cd Release
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --target ALL_BUILD --config Release
```
