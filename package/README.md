# Packaging the application

## Requirements

- Qt Installer Framework (binaries in `PATH`)

# Build package

```sh
cd package
binarycreator -c config/config.xml -p packages FacadeInstaller-version
```
