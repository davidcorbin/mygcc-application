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

After the binary is done building, it should located at `mygcc-application\Release\Release\` with several required DLLs. Notably missing are the Qt5 DLLs. Manually copy `Qt5Core.dll`, `Qt5Gui.dll`, `Qt5Svg.dll`, and `Qt5Widgets.dll` from the `bin` directory of your Qt5 install path for the MSVC version you're using, for example, `C:\Qt\Qt5.10.0\5.10.0\msvc2015\bin` to the Release directory where `facade.exe` is located.

Next, you must copy the resources found in the `mygcc-application\res\` directory and its subdirectories to the `mygcc-application\Release\Release\` directory.

#### Create installer
