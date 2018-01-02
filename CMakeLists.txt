cmake_minimum_required(VERSION 3.0)

project(facade-application)

# Use C++ 14
set(CMAKE_CXX_STANDARD 14)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the Qt5 library
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Svg REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ext/cpr/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ext/json/src)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(ext)

set(SOURCE_FILES src/main.cpp
        src/FileManager.cpp
        src/OS.cpp
        src/SlackFeedback.cpp
        src/types/Course.cpp
        src/ui/MainWindow.cpp
        src/ui/ProfileImage.cpp
        src/ui/Color.cpp
        src/ui/Font.cpp
        src/ui/SidebarPanel.cpp
        src/ui/ProfilePanel.cpp
        src/ui/SidebarLabel.cpp
        src/ui/SidebarIcon.cpp
        src/ui/SidebarListItem.cpp
        src/ui/Image.cpp)

set(HEADER_FILES include/OS.hpp
        include/FileManager.hpp
        include/FileNotFound.hpp
        include/types/Course.hpp
        include/ui/MainWindow.hpp
        include/ui/Color.hpp
        include/ui/Font.hpp
        include/ui/ProfileImage.hpp
        include/ui/ProfilePanel.hpp
        include/ui/SidebarPanel.hpp
        include/ui/SidebarLabel.hpp
        include/ui/SidebarIcon.hpp
        include/ui/SidebarListItem.hpp
        include/ui/Image.hpp)

set(RESOURCE_FILES res/img/default_profile.jpg
        res/font/Lato-Light.ttf
        res/icon/home_normal.svg
        res/icon/home_active.svg
        res/icon/home_selected.svg)

add_executable(facade "${SOURCE_FILES}" "${HEADER_FILES}" "${RESOURCE_FILES}")

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

qt5_use_modules(facade Widgets Svg)

# Use the Widgets module from Qt 5
target_link_libraries(facade Qt5::Widgets)
target_link_libraries(facade Qt5::Svg)
