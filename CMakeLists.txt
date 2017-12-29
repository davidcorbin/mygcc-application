cmake_minimum_required(VERSION 3.0)

project(facade-application)

# Use C++ 14
set(CMAKE_CXX_STANDARD 14)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

set(RESOURCE_FILES res/img/default_profile.jpg
        res/font/Lato-Light.ttf)

# Find the Qt5 library
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ext/cpr/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ext/json/src)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(ext)

add_executable(facade MACOSX_BUNDLE
        src/main.cpp
        src/MainWindow.cpp
        src/SlackFeedback.cpp
        src/ProfileImage.cpp
        include/ProfileImage.hpp
        src/OS.cpp
        include/OS.hpp
        include/Color.hpp
        src/Color.cpp
        src/FileManager.cpp
        include/FileManager.hpp
        include/FileNotFound.hpp
        src/Font.cpp
        include/Font.hpp
        src/ProfilePanel.cpp
        include/ProfilePanel.hpp
        "${RESOURCE_FILES}")

# Use custom macOS settings
if (APPLE)
    set_target_properties(facade PROPERTIES
            MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/res/Info.plist.in
            MACOSX_BUNDLE TRUE
            MACOSX_FRAMEWORK_IDENTIFIER com.facade.Facade
            RESOURCE "${RESOURCE_FILES}"
    )
endif ()

# Add CPR Libraries
target_link_libraries(facade ${CPR_LIBRARIES})

# Include directories 
include_directories(${CPR_INCLUDE_DIRS} ${JSON_INCLUDE_DIRS})

qt5_use_modules(facade Widgets)

# Use the Widgets module from Qt 5
target_link_libraries(facade Qt5::Widgets)
